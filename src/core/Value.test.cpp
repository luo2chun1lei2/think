#include <catch.hpp>

#include <core/Relation.hpp>
#include <core/Value.hpp>

using namespace std;

TEST_CASE("test constant variable", "[core]") {

    SECTION("ConstVar can be set value.") {
        Value var1("var1");

        REQUIRE(var1.get_value_type() == VAR_TYPE_NONE);

        var1.set_value(1);
        REQUIRE(var1.get_value_type() == VAR_TYPE_INT);
        REQUIRE(var1.get_value_as_int() == 1);

        var1.set_value("hello");
        REQUIRE(var1.get_value_type() == VAR_TYPE_STR);
        REQUIRE(var1.get_value_as_str() == "hello");
    }

    SECTION("ConstVar with relation") {
        // My age is 18.
        // - 这里先建立关系
        Object obj1("I");
        Value obj2("value");
        Relation rlt1("age");

        REQUIRE(rlt1.relate({&obj1, &obj2}));

        vector<Object *> found = obj1.get_property("age");
        REQUIRE(found.size() == 1);
        REQUIRE(found[0] == &obj2);

        // - 关系建立后，根据实际情况设置值！
        // - 实际情况是，
        obj2.set_value(18);
        Value *v = dynamic_cast<Value *>(found[0]);
        REQUIRE(v->get_value_as_int() == 18);
    }
}
