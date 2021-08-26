#include <catch.hpp>

#include <core/ObjValue.hpp>
#include <core/RltMath.hpp>

using namespace std;

TEST_CASE("relation plus/minus/multiple/devide", "[ext]") {

    SECTION("plus") {
        // c = a + b
        ObjValue a("a");
        ObjValue b("b");
        ObjValue c("c");
        RltPlus plus("add");

        AsValue(&a)->set_value(Value(123));
        AsValue(&b)->set_value(Value(100));
        plus.relate({&a, &b}, {&c});

        vector<Object *> needs;
        REQUIRE(plus.perform(needs));

        REQUIRE(AsValue(&c)->get_value().get_int() == 223);
    }

    SECTION("minus") {
        // c = a - b
        ObjValue a("a");
        ObjValue b("b");
        ObjValue c("c");
        RltMinus minus("minus");

        AsValue(&a)->set_value(Value(123));
        AsValue(&b)->set_value(Value(100));
        minus.relate({&a, &b}, {&c});

        vector<Object *> needs;
        REQUIRE(minus.perform(needs));

        REQUIRE(AsValue(&c)->get_value().get_int() == 23);
    }

    SECTION("multiple") {
        // c = a * b;
        ObjValue a("a");
        ObjValue b("b");
        ObjValue c("c");
        RltMultiple multiple("multiple"); // 商:quotient

        AsValue(&a)->set_value(Value(17));
        AsValue(&b)->set_value(Value(40));
        multiple.relate({&a, &b}, {&c});

        vector<Object *> needs;
        REQUIRE(multiple.perform(needs));

        REQUIRE(AsValue(&c)->get_value().get_int() == 680);
    }

    SECTION("devide") {
        // c = a / b;
        ObjValue a("a");
        ObjValue b("b");
        ObjValue c("c");
        RltDevide devide("devide"); // 商:quotient

        AsValue(&a)->set_value(Value(200));
        AsValue(&b)->set_value(Value(40));
        devide.relate({&a, &b}, {&c});

        vector<Object *> needs;
        REQUIRE(devide.perform(needs));

        REQUIRE(AsValue(&c)->get_value().get_int() == 5);
    }

    SECTION("equal") {
        // a = b
        ObjValue a("a");
        ObjValue b("b");
        RltEqual equal("equal");

        AsValue(&b)->set_value(Value(99));
        equal.relate({&b}, {&a});

        vector<Object *> needs;
        REQUIRE(equal.perform(needs));

        REQUIRE(AsValue(&a)->get_value().get_int() == 99);
    }

}
