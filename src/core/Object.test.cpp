#include <catch.hpp>

#include <Object.hpp>

TEST_CASE("test element", "[model]") {
    Object obj1("obj1");
    //Object elm2("elm2");

    SECTION("Object has a name.") {
        REQUIRE(!obj1.get_name().empty());
    }

/*
    SECTION("Elements have name.") {
        REQUIRE(elm1.get_name() == "elm1");
        REQUIRE(elm2.get_name() == "elm2");
    }
    */
}
