#include <catch.hpp>

#include <core/Object.hpp>
#include <core/Relation.hpp>

#include <ext/ObjValue.hpp>
#include <fwk/ObjGraphviz.hpp>
#include <fwk/RltShow.hpp>

TEST_CASE("relation show", "[ext][block]") {
    SECTION("equation") {
        // c = (a+b)/2
        // 注意，这里是关系的描述，不是动作，所以“=”是等于，不是赋值。
        Object a("a");
        Object b("b");
        Object c("c");
        ObjValue d("2");
        d.set_value(Value(2));

        Relation plus("+");
        Relation devide("/");
        Relation equal("=");

        REQUIRE(plus.relate({&a, &b}));
        REQUIRE(devide.relate({&plus, &d}));
        REQUIRE(equal.relate({&devide, &c}));

        // Add Graphviz
        ObjGraphviz graphviz("graphviz");

        // Add show relation.
        RltShow show("show");
        show.relate({&graphviz, &c});

        // Perform.
        REQUIRE(show.perform());
    }
}