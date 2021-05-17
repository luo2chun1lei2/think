#include <catch.hpp>

#include <ext/ObjValue.hpp>
#include <ext/RltMath.hpp>

using namespace std;

TEST_CASE("relation plus/minus/multiple/devide", "[ext]") {
#if 0
    SECTION("plus") {
        // c = a + b
        ObjValue a("a");
        ObjValue b("b");
        ObjValue c("c");
        RltPlus plus("add");

        a.set_value(Value(123));
        b.set_value(Value(100));
        plus.relate({&c, &a, &b});

        vector<Object *> needs;
        REQUIRE(plus.perform(needs));

        REQUIRE(c.get_value().get_int() == 223);
    }

    SECTION("minus") {
        // c = a - b
        ObjValue a("a");
        ObjValue b("b");
        ObjValue c("c");
        RltMinus minus("minus");

        a.set_value(Value(123));
        b.set_value(Value(100));
        minus.relate({&c, &a, &b});

        vector<Object *> needs;
        REQUIRE(minus.perform(needs));

        REQUIRE(c.get_value().get_int() == 23);
    }

    SECTION("multiple") {
        // c = a * b;
        ObjValue a("a");
        ObjValue b("b");
        ObjValue c("c");
        RltMultiple multiple("multiple"); // 商:quotient

        a.set_value(Value(17));
        b.set_value(Value(40));
        multiple.relate({&c, &a, &b});

        vector<Object *> needs;
        REQUIRE(multiple.perform(needs));

        REQUIRE(c.get_value().get_int() == 680);
    }

    SECTION("devide") {
        // c = a / b;
        ObjValue a("a");
        ObjValue b("b");
        ObjValue c("c");
        RltDevide devide("devide"); // 商:quotient

        a.set_value(Value(200));
        b.set_value(Value(40));
        devide.relate({&c, &a, &b});

        vector<Object *> needs;
        REQUIRE(devide.perform(needs));

        REQUIRE(c.get_value().get_int() == 5);
    }

    SECTION("equal") {
        // a = b
        ObjValue a("a");
        ObjValue b("b");
        RltEqual equal("equal");

        b.set_value(Value(99));
        equal.relate({&a, &b});

        vector<Object *> needs;
        REQUIRE(equal.perform(needs));

        REQUIRE(a.get_value().get_int() == 99);
    }
#endif
}
