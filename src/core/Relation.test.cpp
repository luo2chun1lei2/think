#include <catch.hpp>

#include <core/Relation.hpp>

/**
 * Relation自己也可以有名字。
 * Relation可以当做object来使用。
 * Relation可以设置多个对象的关联。
 */

TEST_CASE("test relation", "[core][new]") {

    SECTION("Relations have name.") {
        Relation rlt1("rlt1");
        Relation rlt2("rlt2");

        REQUIRE(rlt1.get_name() == "rlt1");
        REQUIRE(rlt2.get_name() == "rlt2");
    }

    SECTION("Create a relation, and add object to it.") {
        Object *obj1 = new Object("obj1");
        Object *obj2 = new Object("obj2");

        Relation *rlt1 = new Relation("rlt1");

        REQUIRE(rlt1->relate({obj1}, {obj2}));
        REQUIRE(rlt1->get_count_of_from_objs() == 1);
        REQUIRE(rlt1->get_count_of_to_objs() == 1);
        REQUIRE(rlt1->get_from_obj(0) == obj1);
        REQUIRE(rlt1->get_to_obj(0) == obj2);

        REQUIRE(obj1->get_count_of_from_rlts() == 1);
        REQUIRE(obj1->get_count_of_to_rlts() == 0);
        REQUIRE(obj1->get_from_rlt(0) == rlt1);

        REQUIRE(obj2->get_count_of_from_rlts() == 0);
        REQUIRE(obj2->get_count_of_to_rlts() == 1);
        REQUIRE(obj2->get_to_rlt(0) == rlt1);

        delete obj1;
        delete obj2;
        delete rlt1;
    }

}
