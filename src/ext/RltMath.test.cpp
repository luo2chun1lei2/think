#include <catch.hpp>

#include <ext/RltMath.hpp>
#include <ext/ObjValue.hpp>

TEST_CASE("relation add", "[ext]") {
    SECTION("add") {
        ObjValue a("a");
        ObjValue b("b");
        Relation add("add");

        a.set_value(Value(123));
        b.set_value(Value(100));
        add.perform();

        // TODO: relation implements IValue.
        //REQUIRE( std::get<int>(add.get_value().get_var()) == 223);    // add = a + b
    }
}