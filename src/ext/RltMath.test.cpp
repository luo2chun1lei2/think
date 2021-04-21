#include <catch.hpp>

#include <ext/ObjValue.hpp>
#include <ext/RltMath.hpp>

TEST_CASE("relation add", "[ext]") {
    SECTION("add") {
        // add = a + b
        ObjValue a("a");
        ObjValue b("b");
        RltPlus plus("add");

        a.set_value(Value(123));
        b.set_value(Value(100));
        plus.relate({&a, &b});

        REQUIRE(plus.perform());

        REQUIRE(plus.get_value().get_int() == 223);
    }

    SECTION("add") {
        // add = a + b
        ObjValue a("a");
        ObjValue b("b");
        RltMinus minus("minus");

        a.set_value(Value(123));
        b.set_value(Value(100));
        minus.relate({&a, &b});

        REQUIRE(minus.perform());

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

        REQUIRE(multiple.perform());

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

        REQUIRE(devide.perform());

        REQUIRE(devide.get_value().get_int() == 5);
    }
/*
    SECTION("equal") {
        ObjValue a("a");
        ObjValue b("b");
        RltAdd add("add");

        a.set_value(Value(123));
        b.set_value(Value(100));
        add.relate({&a, &b});

        REQUIRE(add.perform());

        // TODO: relation implements IValue.
        REQUIRE(add.get_value().get_int() == 223); // add = a + b
    }

    // expression 是表达式， equation是工程式，Identity是恒等式，Formula是普遍规律的公式。
    SECTION("Formula") { 
        ObjValue a("a");
        ObjValue b("b");
        RltAdd add("add");

        a.set_value(Value(123));
        b.set_value(Value(100));
        add.relate({&a, &b});

        REQUIRE(add.perform());

        // TODO: relation implements IValue.
        REQUIRE(add.get_value().get_int() == 223); // add = a + b
    } */
}
