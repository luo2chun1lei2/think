#include <Output.hpp>

#include <array>

#include <Misc.hpp>

using namespace std;

OutputGraphviz::OutputGraphviz() {
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

void OutputGraphviz::finish_graphviz() {
    // 设定layout是格式的，可以是“circo dot fdp neato nop nop1 nop2 osage
    // patchwork sfdp twopi”。
    gvLayout(gvc, g, "dot");

    /* Compute a layout using layout engine from command line args */
    gvLayoutJobs(gvc, g);

    /* Write the graph to file, svg是导出的格式。 */
    gvRenderFilename(gvc, g, "svg", this->output_file_path.c_str());

    /* Free layout data */
    gvFreeLayout(gvc, g);

    /* Free graph structures */
    agclose(g);

    /* close output file, free context */
    gvFreeContext(gvc);
}

bool OutputGraphviz::output(const Model &model) {
    if (!prepare_graphviz()) {
        return false;
    }

    /* Create a simple digraph */
    g = agopen("g", Agdirected, 0);

    size_t count = model.get_elm_count();

    void *ag_elms[ count ];

    // 先处理非Relation的元素。
    for (size_t i = 0; i < count; i++) {
        Element *elm = model.get_elm(i);
        if (typeid(*elm) != typeid(Relation)) {
            string    str_name = elm->get_name();
            char *    name     = const_cast<char *>(str_name.c_str());
            Agnode_t *n        = agnode(g, name, 1); // 1 是固定的。

            /* Set an attribute - in this case one that affects the visible rendering
             */
            agsafeset(n, "color", "blue", "");
            agsafeset(n, "shape", "box", "");

            ag_elms[ i ] = n;
        }
    }

    // 然后再处理Relation的元素。
    for (size_t i = 0; i < count; i++) {
        Element *elm = model.get_elm(i);
        if (typeid(*elm) == typeid(Relation)) {
            Relation *rlt      = dynamic_cast<Relation *>(elm);
            string    str_name = rlt->get_name();
            char *    name     = const_cast<char *>(str_name.c_str());

            int index;
            index       = model.index_of(rlt->get_from()->get_id());
            Agnode_t *f = (Agnode_t *)ag_elms[ index ];

            index       = model.index_of(rlt->get_to()->get_id());
            Agnode_t *t = (Agnode_t *)ag_elms[ index ];

            Agedge_t *e = agedge(g, f, t, name, 1);

            LOGI("NAME=%s\n", name);
            agsafeset(e, "label", name, "");

            ag_elms[ i ] = e;
        }
    }

    finish_graphviz();
    return true;
}
