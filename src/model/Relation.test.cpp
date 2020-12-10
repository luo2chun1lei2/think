#include <catch.hpp>

#include <Relation.hpp>

TEST_CASE("test relation", "[model]") {
    Relation rlt1("rlt1");
    Relation rlt2("rlt2");

    SECTION("Relation has id") {
        REQUIRE(!rlt1.get_id().is_empty());
        REQUIRE(!rlt2.get_id().is_empty());

        REQUIRE(rlt1 != rlt2);
    }

    SECTION("Init by another relation.") {
        Relation rlt3(rlt1);
        REQUIRE(rlt1 == rlt3);
    }

    SECTION("Relation can has relation with two objects") {
        Element elm1("elm1");
        Element elm2("elm2");
        // 建立 elm1 和 elm2 之间的关系。
        rlt1.relate(&elm1, &elm2);

        REQUIRE(elm1 == *(rlt1.get_from()));
        REQUIRE(elm2 == *(rlt1.get_to()));
    }
}
