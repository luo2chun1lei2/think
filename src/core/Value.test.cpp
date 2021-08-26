#include <catch.hpp>

#include <core/Value.hpp>

/**
 * Value 是一个不定类型的值。
 */

TEST_CASE("Value", "[core][new]") {

    SECTION("init") {
        Value v;
        REQUIRE(v.get_type() == Value::TYPE_NONE);
        // REQUIRE(v.get_var() );
    }

    SECTION("value is int") {
        Value v = Value(3);

        REQUIRE(v.get_type() == Value::TYPE_INT);
        REQUIRE(v.get_int() == 3);
    }

    SECTION("value is string") {
        Value v = Value("name");

        REQUIRE(v.get_type() == Value::TYPE_STR);
        REQUIRE(v.get_str() == "name");
    }
}