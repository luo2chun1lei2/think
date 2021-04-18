#include <catch.hpp>

#include <ext/RltMath.hpp>
#include <core/Value.hpp>

TEST_CASE("relation add", "[ext]") {
    SECTION("add") {
        Value a("a");
        Value b("b");
        Relation add("add");

        a.set_value(123);
        b.set_value(100);
        add.perform();

        REQUIRE(add.get_value_as_int() == 223);    // add = a + b
    }
}