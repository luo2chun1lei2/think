#include <catch.hpp>

#include <Object.hpp>
#include <Relation.hpp>
#include <Travel.hpp>
#include <Value.hpp>

#include <vector>

using namespace std;

class MyTravel : public Travel {
public:
    vector<Object *> objs;
    vector<Relation *> rlts;

protected:
    virtual bool on_meet_obj(Object *pobj) {
        objs.push_back(pobj);
        return true;
    }

    virtual bool on_meet_rlt(Relation *prlt) {
        rlts.push_back(prlt);
        return true;
    }

private:
};

/**
 * Travel是在Object之外的机制，Object构成了关系网（Object-Relation Network)，
 * 然后Travel等外部功能去检索、管理这个关系网。
 */
TEST_CASE("test trave", "[action]") {

    /**
     * 建立一个公式。
     */
    SECTION("Create a equation.") {
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

        /**
         * 遍历某个对象相关的关系和对象。
         */
        SECTION("Trave all objects with one object.") {
            MyTravel travel;

            travel.travel(&a);

            REQUIRE(travel.objs.size() == 4);
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &a) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &b) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &c) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &d) != travel.objs.end());

            REQUIRE(travel.rlts.size() == 3);
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &plus) != travel.rlts.end());
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &devide) != travel.rlts.end());
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &equal) != travel.rlts.end());
        }
    }
}