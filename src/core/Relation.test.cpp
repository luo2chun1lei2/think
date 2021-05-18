#include <catch.hpp>

#include <core/Relation.hpp>
#include <ext/ObjValue.hpp>

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

    SECTION("Relation is combined object.") {
        // c = (a+b)/2
        // 注意，这里是关系的描述，不是动作，所以“=”是等于，不是赋值。
        Object a("a");
        Object b("b");
        Object sum("sum");
        ObjValue v_2("2");
        Object quotient("quotient");
        Object c("c");
        
        v_2.set_value(Value(2));

        Relation plus("+");
        Relation devide("/");
        Relation equal("=");

        REQUIRE(plus.relate({&a, &b}, {&sum}));
        REQUIRE(devide.relate({&sum, &v_2}, {&quotient}));
        REQUIRE(equal.relate({&quotient}, {&c}));

        REQUIRE(plus.get_count_of_from_objs() == 2);
        REQUIRE(plus.get_count_of_to_objs() == 1);
        REQUIRE(plus.get_from_obj(0) == &a);
        REQUIRE(plus.get_from_obj(1) == &b);
        REQUIRE(plus.get_to_obj(0) == &sum);

        REQUIRE(devide.get_count_of_from_objs() == 2);
        REQUIRE(devide.get_count_of_to_objs() == 1);
        REQUIRE(devide.get_from_obj(0) == &sum);
        REQUIRE(devide.get_from_obj(1) == &v_2);
        REQUIRE(devide.get_to_obj(0) == &quotient);

        REQUIRE(equal.get_count_of_from_objs() == 1);
        REQUIRE(equal.get_count_of_to_objs() == 1);
        REQUIRE(equal.get_from_obj(0) == &quotient);
        REQUIRE(equal.get_to_obj(0) == &c);

        REQUIRE(a.get_count_of_from_rlts() == 1);
        REQUIRE(a.get_count_of_to_rlts() == 0);
        REQUIRE(a.get_from_rlt(0) == &plus);

        REQUIRE(b.get_count_of_from_rlts() == 1);
        REQUIRE(b.get_count_of_to_rlts() == 0);
        REQUIRE(b.get_from_rlt(0) == &plus);

        REQUIRE(v_2.get_count_of_from_rlts() == 1);
        REQUIRE(v_2.get_count_of_to_rlts() == 0);
        REQUIRE(v_2.get_from_rlt(0) == &devide);

        REQUIRE(c.get_count_of_from_rlts() == 0);
        REQUIRE(c.get_count_of_to_rlts() == 1);
        REQUIRE(c.get_to_rlt(0) == &equal);
    }
}
