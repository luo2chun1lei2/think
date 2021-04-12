#include <catch.hpp>

#include <Relation.hpp>

TEST_CASE("test relation", "[core]") {

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

        REQUIRE(rlt1->set_relation(obj1, obj2));

        REQUIRE(rlt1->get_count_of_objs() == 2);
        REQUIRE(rlt1->get_obj(0) == obj1);
        REQUIRE(rlt1->get_obj(1) == obj2);

        REQUIRE(obj1->get_count_of_rlts() == 1);
        REQUIRE(obj1->get_rlt(0) == rlt1);

        REQUIRE(obj2->get_count_of_rlts() == 1);
        REQUIRE(obj2->get_rlt(0) == rlt1);

        delete obj1;
        delete obj2;
        delete rlt1;
    }
}
