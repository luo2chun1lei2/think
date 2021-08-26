#include <catch.hpp>

#include <core/DynamicInterface.hpp>
#include <core/ObjValue.hpp>
#include <core/Relation.hpp>

using namespace std;

TEST_CASE("object value", "[ext]") {
    SECTION("crash") {
        ObjValue var1("var1");

        InterfaceValue *ivalue1 = AsValue(var1);

        REQUIRE(ivalue1 != NULL);
        ivalue1->set_value(Value(1));
        REQUIRE(ivalue1->get_value().get_int() == 1);
    }

    SECTION("set value") {
        Value v;

        ObjValue var1("var1");

        v = AsValue(var1)->get_value();
        REQUIRE(v.get_type() == Value::TYPE_NONE);

        AsValue(var1)->set_value(Value(1));
        v = AsValue(var1)->get_value();
        REQUIRE(v.get_type() == Value::TYPE_INT);
        REQUIRE(v.get_int() == 1);

        AsValue(var1)->set_value(Value("hello"));
        v = AsValue(var1)->get_value();
        REQUIRE(v.get_type() == Value::TYPE_STR);
        REQUIRE(v.get_str() == "hello");
    }

    SECTION("ConstVar with relation") {
        // My age is 18.
        // - 这里先建立关系
        Object obj1("I");
        ObjValue obj2("value");
        Relation rlt1("age");

        REQUIRE(rlt1.relate({&obj1}, {&obj2}));

        vector<Object *> found = obj1.get_property("age");
        REQUIRE(found.size() == 1);
        REQUIRE(found[0] == &obj2);

        // - 关系建立后，根据实际情况设置值！
        // - 实际情况是，
        AsValue(obj2)->set_value(18);
        ObjValue *v = dynamic_cast<ObjValue *>(found[0]);
        REQUIRE(AsValue(*v)->get_value().get_int() == 18);
    }

    SECTION("Create a OR-Net.") {
        // c = (a+b)/2
        // 注意，这里是关系的描述，不是动作，所以“=”是等于，不是赋值。
        Object a("a");
        Object b("b");
        Object sum("sum");
        ObjValue v_2("2");
        Object quotient("quotient");
        Object c("c");

        AsValue(v_2)->set_value(Value(2));

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
