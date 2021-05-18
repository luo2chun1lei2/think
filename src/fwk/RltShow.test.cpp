#include <catch.hpp>

#include <core/Object.hpp>
#include <core/Relation.hpp>

#include <ext/ObjValue.hpp>
#include <fwk/ObjGraphviz.hpp>
#include <fwk/RltShow.hpp>

TEST_CASE("relation show", "[ext][block]") {
    SECTION("equation") {
        Object a("a");
        Object b("b");
        Object sum("sum");
        ObjValue v_2("2");
        Object quotient("quotient");
        Object c("c");

        v_2.set_value(Value(2));

        Relation plus("+");
        Relation devide("/");
        Relation equal("=");

        REQUIRE(plus.relate({&a, &b}, {&sum}));
        REQUIRE(devide.relate({&sum, &v_2}, {&quotient}));
        REQUIRE(equal.relate({&quotient}, {&c}));

        REQUIRE(plus.get_count_of_from_objs() == 2);
        REQUIRE(plus.get_count_of_to_objs() == 1);
        REQUIRE(plus.get_from_obj(0) == &a);
        REQUIRE(plus.get_from_obj(1) == &b);
        REQUIRE(plus.get_to_obj(0) == &sum);

        REQUIRE(devide.get_count_of_from_objs() == 2);
        REQUIRE(devide.get_count_of_to_objs() == 1);
        REQUIRE(devide.get_from_obj(0) == &sum);
        REQUIRE(devide.get_from_obj(1) == &v_2);
        REQUIRE(devide.get_to_obj(0) == &quotient);

        REQUIRE(equal.get_count_of_from_objs() == 1);
        REQUIRE(equal.get_count_of_to_objs() == 1);
        REQUIRE(equal.get_from_obj(0) == &quotient);
        REQUIRE(equal.get_to_obj(0) == &c);

        REQUIRE(a.get_count_of_from_rlts() == 1);
        REQUIRE(a.get_count_of_to_rlts() == 0);
        REQUIRE(a.get_from_rlt(0) == &plus);

        REQUIRE(b.get_count_of_from_rlts() == 1);
        REQUIRE(b.get_count_of_to_rlts() == 0);
        REQUIRE(b.get_from_rlt(0) == &plus);

        REQUIRE(v_2.get_count_of_from_rlts() == 1);
        REQUIRE(v_2.get_count_of_to_rlts() == 0);
        REQUIRE(v_2.get_from_rlt(0) == &devide);

        REQUIRE(c.get_count_of_from_rlts() == 0);
        REQUIRE(c.get_count_of_to_rlts() == 1);
        REQUIRE(c.get_to_rlt(0) == &equal);

        SECTION("show") {
            // Add Graphviz
            ObjGraphviz graphviz("graphviz");

            // Add show relation.
            RltShow show("show");
            show.relate({&c}, {&graphviz});

            // Perform.
            REQUIRE(show.perform());
        }
    }
}