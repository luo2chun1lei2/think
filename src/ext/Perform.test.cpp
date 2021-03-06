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

        equal.relate({&b}, {&a});

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

        plus.relate({&a, &b}, {&c});

        a.set_value(Value(100));
        b.set_value(Value(20));

        PerformRound perform(-1);
        REQUIRE(perform.perform(&c));

        REQUIRE(c.get_value().get_type() == Value::TYPE_INT);
        REQUIRE(c.get_value().get_int() == 120);
    }

    SECTION("Formula3") {
        // c = b + a / 5
        ObjValue a("a");
        ObjValue b("b");
        ObjValue c("c");
        ObjValue v5("5");
        ObjValue tmp1("tmp1");
        ObjValue tmp2("tmp2");

        RltPlus plus("plus");
        RltDevide devide("devide");
        RltEqual equal("equal");

        devide.relate({&a, &v5}, {&tmp1});
        plus.relate({&b, &tmp1}, {&tmp2});
        equal.relate({&tmp2}, {&c});

        a.set_value(Value(100));
        b.set_value(Value(20));
        v5.set_value(Value(5));

        PerformRound perform(-1);
        REQUIRE(perform.perform(&c));

        REQUIRE(c.get_value().get_type() == Value::TYPE_INT);
        REQUIRE(c.get_value().get_int() == 40);
    }
}
