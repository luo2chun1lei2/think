#include <catch.hpp>

#include <core/Relation.hpp>
#include <core/Value.hpp>

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

        REQUIRE(rlt1->relate({obj1, obj2}));

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

    SECTION("Relation is combined object.") {
        // c = (a+b)/2
        // 注意，这里是关系的描述，不是动作，所以“=”是等于，不是赋值。
        Object a("a");
        Object b("b");
        Object c("c");
        Value d("2");
        d.set_value(2);

        Relation plus("+");
        Relation devide("/");
        Relation equal("=");

        REQUIRE(plus.relate({&a, &b}));
        REQUIRE(devide.relate({&plus, &d}));
        REQUIRE(equal.relate({&c, &devide}));

        REQUIRE(plus.get_count_of_objs() == 2);
        REQUIRE(plus.get_obj(0) == &a);
        REQUIRE(plus.get_obj(1) == &b);

        REQUIRE(plus.get_count_of_rlts() == 1);
        REQUIRE(plus.get_rlt(0) == &devide);

        REQUIRE(devide.get_count_of_objs() == 2);
        REQUIRE(devide.get_obj(0) == &plus);
        REQUIRE(devide.get_obj(1) == &d);

        REQUIRE(devide.get_count_of_rlts() == 1);
        REQUIRE(devide.get_rlt(0) == &equal);

        REQUIRE(equal.get_count_of_objs() == 2);
        REQUIRE(equal.get_obj(0) == &c);
        REQUIRE(equal.get_obj(1) == &devide);

        REQUIRE(equal.get_count_of_rlts() == 0);

        REQUIRE(a.get_count_of_rlts() == 1);
        REQUIRE(a.get_rlt(0) == &plus);

        REQUIRE(b.get_count_of_rlts() == 1);
        REQUIRE(b.get_rlt(0) == &plus);

        REQUIRE(c.get_count_of_rlts() == 1);
        REQUIRE(c.get_rlt(0) == &equal);

        REQUIRE(d.get_count_of_rlts() == 1);
        REQUIRE(d.get_rlt(0) == &devide);
    }
}
