#include <catch.hpp>

#include <ext/ObjValue.hpp>
#include <ext/RltMath.hpp>

using namespace std;

TEST_CASE("relation plus/minus/multiple/devide", "[ext]") {
    SECTION("plus") {
        // add = a + b
        ObjValue a("a");
        ObjValue b("b");
        RltPlus plus("add");

        a.set_value(Value(123));
        b.set_value(Value(100));
        plus.relate({&a, &b});

        vector<Object *> needs;
        REQUIRE(plus.perform(needs));

        REQUIRE(plus.get_value().get_int() == 223);
    }

    SECTION("minus") {
        // add = a + b
        ObjValue a("a");
        ObjValue b("b");
        RltMinus minus("minus");

        a.set_value(Value(123));
        b.set_value(Value(100));
        minus.relate({&a, &b});

        vector<Object *> needs;
        REQUIRE(minus.perform(needs));

        REQUIRE(minus.get_value().get_int() == 23);
    }

    SECTION("multiple") {
         // devide = a / b;
        ObjValue a("a");
        ObjValue b("b");
        RltMultiple multiple ("multiple"); // 商:quotient

        a.set_value(Value(17));
        b.set_value(Value(40));
        multiple.relate({&a, &b});

        vector<Object *> needs;
        REQUIRE(multiple.perform(needs));

        REQUIRE(multiple.get_value().get_int() == 680);
    }

    SECTION("devide") {
         // devide = a / b;
        ObjValue a("a");
        ObjValue b("b");
        RltDevide devide ("devide"); // 商:quotient

        a.set_value(Value(200));
        b.set_value(Value(40));
        devide.relate({&a, &b});

        vector<Object *> needs;
        REQUIRE(devide.perform(needs));

        REQUIRE(devide.get_value().get_int() == 5);
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
}
