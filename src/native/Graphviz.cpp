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

    n = agnode(g, NULL, 1); // 1 是固定的。
    agsafeset(n, "label", (char *)str.c_str(), "");

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
