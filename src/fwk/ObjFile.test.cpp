#include <catch.hpp>

#include <fwk/ObjFile.hpp>
#include <fwk/ObjProcessor.hpp>
#include <fwk/RltPipe.hpp>

TEST_CASE("FileLine", "[fwk]") {
    SECTION("read") {
        FileLine line("File");
        RltPipeLine pipe("pipe");
        ObjProcessorLine process("process");

        REQUIRE(pipe.relate({&line, &process}));

        std::vector<Object *> need_objs;
        REQUIRE(pipe.perform(need_objs));
    }
}