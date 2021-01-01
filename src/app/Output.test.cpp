#include <catch.hpp>

#include <stdlib.h>
#include <unistd.h>

#include <sstream>

#include <Misc.hpp>
#include <Output.hpp>

using namespace std;

// 此测试会阻塞，直到关闭eog程序。
TEST_CASE("test output about graphviz", "[app][block]") {
    Element elm0("elm0"); // not in model.
    Element elm1("elm1");
    Element elm2("elm2");
    Element elm3("elm3");

    Relation rlt0("rlt0"); // not in model.
    Relation rlt1("rlt1");
    Relation rlt2("rlt2");

    Model model("model");

    model.add_elm(&elm1);
    model.add_elm(&elm2);
    model.add_elm(&elm3);

    rlt1.relate(&elm1, &elm2);
    rlt2.relate(&elm2, &elm3);

    model.add_elm(&rlt1);
    model.add_elm(&rlt2);

    SECTION("init and export") {
        OutputGraphviz output("test");
        char           path[] = "/tmp/XXXXXX.svg";
        int            fd     = mkstemps(path, 4);
        REQUIRE(fd != -1);
        close(fd);

        output.set_output_filepath(path);
        LOGI("path=%s\n", path);
        REQUIRE(output.output(&model));

        // 执行显示图片的命令，system必须退出才行。
        ostringstream stream;
        stream << "eog " << path;
        auto cmd = stream.str();
        system(cmd.c_str());
    }
}
