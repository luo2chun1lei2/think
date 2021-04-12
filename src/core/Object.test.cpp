#include <catch.hpp>

#include <Object.hpp>

TEST_CASE("test object", "[core]") {
    Object obj1("obj1");
    Object obj2("obj2");

    SECTION("Object has a name.") {
        REQUIRE(!obj1.get_name().empty());
        REQUIRE(obj1.get_name() == "obj1");

        REQUIRE(!obj2.get_name().empty());
        REQUIRE(obj2.get_name() == "obj2");
    }

    SECTION("Objects have property.") {
        // obj1.set_property();
    }
}
