#include <fwk/ObjGraphviz.hpp>

#include <misc/Misc.hpp>

#include <stdlib.h>
#include <unistd.h>

#include <sstream>

using namespace std;

ObjGraphviz::ObjGraphviz(const std::string name)
    : Object(name) {
    graphviz = new Graphviz(name.c_str(), Graphviz::GRAPH_SVG, Graphviz::TYPE_BASIC);

    // create temp file to save temp file.
    char path[] = "/tmp/XXXXXX.svg";
    int fd = mkstemps(path, 4);
    close(fd);

    graphviz->set_output_filepath(path);
}

ObjGraphviz::~ObjGraphviz() {
    delete graphviz;
}

bool ObjGraphviz::begin_notify() {
    graphviz->prepare_graphviz();
    return true;
}

bool ObjGraphviz::notify(Object *obj) {

    // 因为Graphviz的特点，必须是先绘制节点，然后再绘制边。
    Relation *rlt = dynamic_cast<Relation *>(obj);
    if (rlt) {
        this->notified_relations.push_back(rlt);
    } else { // type = Object.
        this->notified_objects.push_back(obj);
    }
    return true;
}

// 注意下面的绘制：Object 和 Relation 都是Node，然后之间用节点相连。
bool ObjGraphviz::end_notify() {

    for (Object *obj : notified_objects) {
        Agnode_t *node = graphviz->add_node(obj->get_name().c_str(), true);
        obj_nodes[obj] = node;
    }

    for (Relation *rlt : notified_relations) {
        Agnode_t *node = graphviz->add_node(rlt->get_name().c_str(), false);
        obj_nodes[rlt] = node;
    }

    for (Relation *rlt : notified_relations) {

        if (rlt->get_objects().size() < 2) {
            LOGE("Cannot draw a edge(%s) if it has only ONE edge.\n", rlt->get_name().c_str());
            return false;
        }

        // edge is from "rlt" to all own objects.
        Agnode_t *rlt_node = obj_nodes[rlt];

        for (Object *to : rlt->get_objects()) {
            Agnode_t *to_node = obj_nodes[to];
            Agedge_t *edge1 = graphviz->add_edge("", rlt_node, to_node);

            // rlt_edges[rlt] = edge;
        }
    }

    graphviz->finish_graphviz();
LOGI("HERE\n");
    // 执行显示图片的命令，system必须退出才行。
    ostringstream stream;
    stream << "eog " << graphviz->get_output_filepath();
    auto cmd = stream.str();
    system(cmd.c_str());

    return true;
}