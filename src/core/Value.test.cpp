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

    // TODO: 暂时不进行复杂和多的测试，毕竟可能修改会很多。
}