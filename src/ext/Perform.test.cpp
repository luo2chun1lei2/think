#include <catch.hpp>

#include <ext/ObjValue.hpp>
#include <ext/Perform.hpp>
#include <ext/RltMath.hpp>

TEST_CASE("PerformRound", "[ext]") {

    SECTION("Formula1") {
        // a = b
        ObjValue a("a");
        ObjValue b("b");

        RltEqual equal("equal");

        equal.relate({&a, &b});

        b.set_value(Value(100));

        PerformRound perform(10);
        REQUIRE(perform.perform(&a));

        REQUIRE(a.get_value().get_type() == Value::TYPE_INT);
        REQUIRE(a.get_value().get_int() == 100);
    }

    SECTION("Formula2") {
        // c = a + b
        ObjValue a("a");
        ObjValue b("b");
        ObjValue c("c");

        RltPlus plus("plus");
        RltEqual equal("equal");

        plus.relate({&a, &b});
        equal.relate({&c, &plus});

        a.set_value(Value(100));
        b.set_value(Value(20));

        PerformRound perform(-1);
        REQUIRE(perform.perform(&c));

        REQUIRE(c.get_value().get_type() == Value::TYPE_INT);
        REQUIRE(c.get_value().get_int() == 120);
    }

    SECTION("Formula3") {
        // c = a + b / 5
        ObjValue a("a");
        ObjValue b("b");
        ObjValue c("c");
        ObjValue d("5");
        RltPlus plus("plus");
        RltDevide devide("devide");
        RltEqual equal("equal");

        devide.relate({&b, &d});
        plus.relate({&a, &devide});
        equal.relate({&c, &plus});

        a.set_value(Value(100));
        b.set_value(Value(20));
        d.set_value(Value(5));

        PerformRound perform(-1);
        REQUIRE(perform.perform(&c));

        REQUIRE(c.get_value().get_type() == Value::TYPE_INT);
        REQUIRE(c.get_value().get_int() == 104);
    }
}

TEST_CASE("Perform", "[ext]") {
    /*
        SECTION("Formula1") {
            // a = b
            ObjValue a("a");
            ObjValue b("b");

            RltEqual equal("equal");

            equal.relate({&a, &b});

            a.set_value(Value(100));

            Perform perform;
            REQUIRE(perform.perform(&a));

            REQUIRE(a.get_value().get_int() == 100);
        }

        SECTION("Formula2") {
            // c = a + b
            ObjValue a("a");
            ObjValue b("b");
            ObjValue c("c");

            RltPlus plus("plus");
            RltEqual equal("equal");

            plus.relate({&a, &b});
            equal.relate({&c, &plus});

            a.set_value(Value(100));
            b.set_value(Value(20));

            Perform perform;
            REQUIRE(perform.perform(&c));

            //REQUIRE(c.get_value().get_int() == 120);
        }
    */
    /*
SECTION("Formula3") {
    // c = a + b / 5
    ObjValue a("a");
    ObjValue b("b");
    ObjValue c("c");
    ObjValue d("5");
    RltPlus plus("plus");
    RltDevide devide("devide");
    RltEqual equal("equal");

    devide.relate({&b, &d});
    plus.relate({&a, &devide});
    equal.relate({&c, &plus});

    a.set_value(Value(100));
    b.set_value(Value(20));
    d.set_value(Value(5));

    REQUIRE(equal.perform());

    REQUIRE(c.get_value().get_int() == 104);
} */
}