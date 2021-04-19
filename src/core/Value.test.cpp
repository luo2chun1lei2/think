#include <catch.hpp>

#include <core/Value.hpp>

TEST_CASE("Value", "[core]") {
    SECTION("init") {
        Value v;
        REQUIRE(v.get_type() == Value::TYPE_NONE);
        //REQUIRE(v.get_var() );
    }
}