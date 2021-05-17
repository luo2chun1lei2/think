#include <catch.hpp>

#include <stdlib.h>
#include <unistd.h>

#include <sstream>

#include <misc/Misc.hpp>
#include <native/Graphviz.hpp>

using namespace std;

TEST_CASE("graphviz", "[misc][block]") {
    SECTION("draw a graphviz") {
        Graphviz output("test", Graphviz::GRAPH_SVG, Graphviz::TYPE_BASIC);
        char path[] = "/tmp/XXXXXX.svg";
        int fd = mkstemps(path, 4);
        REQUIRE(fd != -1);
        close(fd);

        output.set_output_filepath(path);
        LOGI("path=%s\n", path);

        // REQUIRE(output.output(&model));
        output.prepare_graphviz();
        Agnode_t *f = output.add_node("abc", true);
        Agnode_t *t = output.add_node("123", false);
        output.add_edge("link", f, t);
        output.finish_graphviz();

        // 执行显示图片的命令，system必须退出才行。
        ostringstream stream;
        stream << "eog " << path;
        auto cmd = stream.str();
        system(cmd.c_str());
    }
}