#include <catch.hpp>

#include <ext/ObjValue.hpp>
#include <ext/RltMath.hpp>

TEST_CASE("relation add", "[ext]") {
    SECTION("add") {
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
}
