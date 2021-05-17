#include <native/Graphviz.hpp>

#include <vector>

#include <misc/Misc.hpp>

using namespace std;

Graphviz::Graphviz(const string name, Graphviz::Option option, Graphviz::Type type)
    : option(option)
    , type(type) {
}

Graphviz::~Graphviz() {
}

void Graphviz::set_output_filepath(const std::string path) {
    output_file_path = path;
}

std::string Graphviz::get_output_filepath() {
    return output_file_path;
}

bool Graphviz::prepare_graphviz() {
    /* set up a graphviz context */
    gvc = gvContext();

    // 创建一个有向图 Agdirected
    g = agopen("g", Agdirected, 0);

    return true;
}

void Graphviz::finish_graphviz() {
    // 设定layout是格式的，可以是“circo dot fdp neato nop nop1 nop2 osage
    // patchwork sfdp twopi”。
    // dot: 是按照层级来安排节点
    // circo: 是一个中心，显然其他的节点向四周扩散的方法。
    // neato: 会重叠，和circo有点像。
    // ...

    if (type == TYPE_LIST) {
        // LIST时，横屏显示。
        agsafeset(g, "rankdir", "LR", "");
    }

    gvLayout(gvc, g, "dot");

    /* Write the graph to file, svg、plain是导出的格式。 */
    if (option == GRAPH_TEXT) {
        gvRenderFilename(gvc, g, "plain", this->output_file_path.c_str());
    } else { // GRAPH_SVG : 缺省！
        gvRenderFilename(gvc, g, "svg", this->output_file_path.c_str());
    }

    /* Free layout data */
    gvFreeLayout(gvc, g); // TODO: 单独运行时，发现有重复释放资源的问题，将这个注释，就没有了。

    /* Free graph structures */
    agclose(g);

    /* close output file, free context */
    gvFreeContext(gvc);
}

Agnode_t *Graphviz::add_node(const std::string str, bool is_node) {
    Agnode_t *n;

    n = agnode(g, (char *)str.c_str(), 1); // 1 是固定的。

    /* 设置节点的属性 */
    if (is_node) {
        agsafeset(n, "color", "blue", "");
        agsafeset(n, "shape", "box", "");
    } else {
        agsafeset(n, "color", "green", "");
        agsafeset(n, "shape", "diamond", "");
    }

    return n;
}

Agedge_t *Graphviz::add_edge(const std::string str, Agnode_t *f, Agnode_t *t) {
    Agedge_t *e = agedge(g, f, t, NULL, 1);

    agsafeset(e, "label", (char *)str.c_str(), "");
    agsafeset(e, "color", "black", "");

    return e;
}

#if 0
bool Graphviz::output(const Model *model) {
    if (!prepare_graphviz()) {
        return false;
    }

    // 创建一个有向图 Agdirected
    g = agopen("g", Agdirected, 0);

    size_t count = model->get_elm_count();

    void *ag_elms[count];

    memset(ag_elms, 0, sizeof(ag_elms));

    // 先处理非Relation的元素。
    for (size_t i = 0; i < count; i++) {
        Element *elm = model->get_elm(i);
        //Relation * rlt = dynamic_cast<Relation *>elm;
        if (typeid(*elm) != typeid(Relation)) { // TODO: 类型判断有问题。

            string str_name = elm->get_name();
            if (str_name.length() == 0) {
                //名字是空，就是匿名的，不要显示。
                continue;
            }

            char *name = const_cast<char *>(str_name.c_str());

            vector<Element *> elm_descs = model->find_elm_by_rlt(elm->get_name(), "desc");
            string str_desc;
            char *desc = NULL;
            if (elm_descs.size()) {
                str_desc = elm_descs[0]->get_value();
                desc = const_cast<char *>(str_desc.c_str());
            }

            Agnode_t *n;
            if (desc == NULL) {
                n = agnode(g, name, 1); // 1 是固定的。
            } else {
                n = agnode(g, desc, 1); // 1 是固定的。
            }

            /* 设置节点的属性 */
            agsafeset(n, "color", "blue", "");
            agsafeset(n, "shape", "box", "");

            // LOGI("node: %s\n", name);

            ag_elms[i] = n;
        }
    }

    // 然后再处理Relation的元素，作为边。
    for (size_t i = 0; i < count; i++) {
        Element *elm = model->get_elm(i);
        if (typeid(*elm) == typeid(Relation)) {
            Relation *rlt = dynamic_cast<Relation *>(elm);
            string str_name = rlt->get_name();
            char *name = const_cast<char *>(str_name.c_str());

            if (!rlt->get_from()) {
                LOGE("Relation(%s) hasn't from.\n", name);
                return false;
            }

            if (!rlt->get_to()) {
                LOGE("Relation(%s) hasn't to.\n", name);
                return false;
            }

            if (rlt->get_from()->get_name().length() == 0 || rlt->get_to()->get_name().length() == 0) {
                // relation相关的元素如果是匿名的，就不显示。
                continue;
            }

            // LOGI("%s --%S-> %s\n", rlt->get_from()->get_name().c_str(), name, rlt->get_to()->get_name().c_str());
            int index;
            index = model->index_of(rlt->get_from()->get_id());
            Agnode_t *f = (Agnode_t *)ag_elms[index];
            if (index == -1 || !f) {
                LOGE("Relation(%s) cannot find from node.\n", name);
                return false;
            }

            index = model->index_of(rlt->get_to()->get_id());
            Agnode_t *t = (Agnode_t *)ag_elms[index];
            if (index == -1 || !t) {
                LOGE("Relation(%s) cannot find to node.\n", name);
                return false;
            }

            Agedge_t *e = agedge(g, f, t, NULL, 1);

            agsafeset(e, "label", name, "");
            agsafeset(e, "color", "black", "");

            ag_elms[i] = e;
        }
    }

    if (type == TYPE_LIST) {
        // LIST时，横屏显示。
        agsafeset(g, "rankdir", "LR", "");
    }

    finish_graphviz();

    return true;
}
#endif