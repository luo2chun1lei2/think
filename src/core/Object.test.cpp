#include <catch.hpp>

#include <core/Object.hpp>

using namespace std;

TEST_CASE("test object", "[core]") {

    SECTION("Object has a name.") {
        Object obj1("obj1");
        Object obj2("obj2");

        REQUIRE(!obj1.get_name().empty());
        REQUIRE(obj1.get_name() == "obj1");

        REQUIRE(!obj2.get_name().empty());
        REQUIRE(obj2.get_name() == "obj2");
    }

    SECTION("Add a relation.") {
        Object obj1("obj1");
        Relation rlt1("rlt1");
        Relation rlt2("rlt2");
        Relation *prlt;

        REQUIRE(obj1.get_count_of_from_rlts() == 0);
        obj1.add_from_rlt(&rlt1);
        REQUIRE(obj1.get_count_of_from_rlts() == 1);
        prlt = obj1.get_from_rlt(0);
        REQUIRE(prlt->get_name() == "rlt1");

        REQUIRE(obj1.get_count_of_to_rlts() == 0);
        obj1.add_to_rlt(&rlt2);
        REQUIRE(obj1.get_count_of_to_rlts() == 1);
        prlt = obj1.get_to_rlt(0);
        REQUIRE(prlt->get_name() == "rlt2");
    }

    SECTION("Ger property by relation.") {
        Object obj1("obj1");
        Object obj2("obj2");
        Relation rlt1("rlt1");

        REQUIRE(rlt1.relate({&obj1}, {&obj2}));

        vector<Object *> found = obj1.get_property("rlt1");
        REQUIRE(found.size() == 1);
        REQUIRE(found[0] == &obj2);
    }
}
