#include <catch.hpp>

#include <fwk/FileLine.hpp>

TEST_CASE("FileLine", "[fwk]")
{
    SECTION("read") {
        FileLine line("File");
        RltPipeLine pipe("pipe");
        ObjProcessLine process("process");

        REQUIRE(pipe.relate({&line, &process}));

        std::vector<Object *> need_objs;
        REQUIRE(pipe.perform(need_objs));
    }
}