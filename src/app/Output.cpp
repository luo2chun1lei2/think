#include <Output.hpp>

#include <array>

#include <Misc.hpp>

using namespace std;

OutputGraphviz::OutputGraphviz(const string name)
    : Output(name) {
}

OutputGraphviz::~OutputGraphviz() {
}

void OutputGraphviz::set_output_filepath(const std::string path) {
    output_file_path = path;
}

bool OutputGraphviz::prepare_graphviz() {
    /* set up a graphviz context */
    gvc = gvContext();

    return true;
}

void OutputGraphviz::finish_graphviz2() {
    // 设定layout是格式的，可以是“circo dot fdp neato nop nop1 nop2 osage
    // patchwork sfdp twopi”。
    gvLayout(gvc, g, "dot");

    /* Compute a layout using layout engine from command line args */
    gvLayoutJobs(gvc, g);

    /* Write the graph to file, svg是导出的格式。 */
    gvRenderFilename(gvc, g, "plain", this->output_file_path.c_str());

    /* Free layout data */
    // gvFreeLayout(gvc, g); //TODO: 单独运行时，发现有重复释放资源的问题，将这个注释，就没有了。

    /* Free graph structures */
    agclose(g);

    /* close output file, free context */
    gvFreeContext(gvc);
}

void OutputGraphviz::finish_graphviz() {
    // 设定layout是格式的，可以是“circo dot fdp neato nop nop1 nop2 osage
    // patchwork sfdp twopi”。
    gvLayout(gvc, g, "dot");

    /* Compute a layout using layout engine from command line args */
    gvLayoutJobs(gvc, g);

    /* Write the graph to file, svg是导出的格式。 */
    gvRenderFilename(gvc, g, "svg", this->output_file_path.c_str());

    /* Free layout data */
    // gvFreeLayout(gvc, g); //TODO: 单独运行时，发现有重复释放资源的问题，将这个注释，就没有了。

    /* Free graph structures */
    agclose(g);

    /* close output file, free context */
    gvFreeContext(gvc);
}

bool OutputGraphviz::output(const Model *model) {
    if (!prepare_graphviz()) {
        return false;
    }

    /* Create a simple digraph */
    g = agopen("g", Agdirected, 0);

    size_t count = model->get_elm_count();

    void *ag_elms[ count ];

    memset(ag_elms, 0, sizeof(ag_elms));

    // 先处理非Relation的元素。
    for (size_t i = 0; i < count; i++) {
        Element *elm = model->get_elm(i);
        if (typeid(*elm) != typeid(Relation)) {
            string    str_name = elm->get_name();
            char *    name     = const_cast<char *>(str_name.c_str());
            Agnode_t *n        = agnode(g, name, 1); // 1 是固定的。

            /* 设置节点的属性 */
            agsafeset(n, "color", "blue", "");
            agsafeset(n, "shape", "box", "");

            // LOGI("node: %s\n", name);

            ag_elms[ i ] = n;
        }
    }

    // 然后再处理Relation的元素。
    for (size_t i = 0; i < count; i++) {
        Element *elm = model->get_elm(i);
        if (typeid(*elm) == typeid(Relation)) {
            Relation *rlt      = dynamic_cast<Relation *>(elm);
            string    str_name = rlt->get_name();
            char *    name     = const_cast<char *>(str_name.c_str());

            if (!rlt->get_from()) {
                LOGE("Relation(%s) hasn't from.\n", name);
                return false;
            }

            if (!rlt->get_to()) {
                LOGE("Relation(%s) hasn't to.\n", name);
                return false;
            }

            // LOGI("%s --%S-> %s\n", rlt->get_from()->get_name().c_str(), name, rlt->get_to()->get_name().c_str());
            int index;
            index       = model->index_of(rlt->get_from()->get_id());
            Agnode_t *f = (Agnode_t *)ag_elms[ index ];
            if (index == -1 || !f) {
                LOGE("Relation(%s) cannot find from node.\n", name);
                return false;
            }

            index       = model->index_of(rlt->get_to()->get_id());
            Agnode_t *t = (Agnode_t *)ag_elms[ index ];
            if (index == -1 || !t) {
                LOGE("Relation(%s) cannot find to node.\n", name);
                return false;
            }

            Agedge_t *e = agedge(g, f, t, NULL, 1);

            agsafeset(e, "label", name, "");
            agsafeset(e, "color", "black", "");

            ag_elms[ i ] = e;
        }
    }

    finish_graphviz();
    return true;
}

bool OutputGraphviz::output2(const Model *model) {
    if (!prepare_graphviz()) {
        return false;
    }

    /* Create a simple digraph */
    g = agopen("g", Agdirected, 0);

    size_t count = model->get_elm_count();

    void *ag_elms[ count ];

    memset(ag_elms, 0, sizeof(ag_elms));

    // 先处理非Relation的元素。
    for (size_t i = 0; i < count; i++) {
        Element *elm = model->get_elm(i);
        if (typeid(*elm) != typeid(Relation)) {
            string    str_name = elm->get_name();
            char *    name     = const_cast<char *>(str_name.c_str());
            Agnode_t *n        = agnode(g, name, 1); // 1 是固定的。

            /* 设置节点的属性 */
            agsafeset(n, "color", "blue", "");
            agsafeset(n, "shape", "box", "");

            // LOGI("node: %s\n", name);

            ag_elms[ i ] = n;
        }
    }

    // 然后再处理Relation的元素。
    for (size_t i = 0; i < count; i++) {
        Element *elm = model->get_elm(i);
        if (typeid(*elm) == typeid(Relation)) {
            Relation *rlt      = dynamic_cast<Relation *>(elm);
            string    str_name = rlt->get_name();
            char *    name     = const_cast<char *>(str_name.c_str());

            if (!rlt->get_from()) {
                LOGE("Relation(%s) hasn't from.\n", name);
                return false;
            }

            if (!rlt->get_to()) {
                LOGE("Relation(%s) hasn't to.\n", name);
                return false;
            }

            // LOGI("%s --%S-> %s\n", rlt->get_from()->get_name().c_str(), name, rlt->get_to()->get_name().c_str());
            int index;
            index       = model->index_of(rlt->get_from()->get_id());
            Agnode_t *f = (Agnode_t *)ag_elms[ index ];
            if (index == -1 || !f) {
                LOGE("Relation(%s) cannot find from node.\n", name);
                return false;
            }

            index       = model->index_of(rlt->get_to()->get_id());
            Agnode_t *t = (Agnode_t *)ag_elms[ index ];
            if (index == -1 || !t) {
                LOGE("Relation(%s) cannot find to node.\n", name);
                return false;
            }

            Agedge_t *e = agedge(g, f, t, name, 1);

            agsafeset(e, "label", name, "");
            agsafeset(e, "color", "black", "");

            ag_elms[ i ] = e;
        }
    }

    finish_graphviz2();
    return true;
}
