#include <catch.hpp>

#include <core/Object.hpp>
#include <core/Relation.hpp>

#include <ext/ObjValue.hpp>
#include <ext/Travel.hpp>

#include <misc/Misc.hpp>

#include <vector>

using namespace std;

class MyTravel : public Travel {
public:
    vector<Object *> objs;
    vector<Relation *> rlts;

    virtual void print() {
        for(Object *obj : objs) {
            printf("%s ", obj->get_name().c_str());
        }
        printf("\n");

        for(Relation *rlt : rlts) {
            printf("%s ", rlt->get_name().c_str());
        }
        printf("\n");
    }

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
TEST_CASE("travel", "[ext]") {

    SECTION("simple example.") {
        // c = (a+b)/2
        // 注意，这里是关系的描述，不是动作，所以“=”是等于，不是赋值。
        Object a("a");
        Object b("b");
        Object c("c");

        Relation ab("a->b");
        Relation bc("b->c");

        REQUIRE(ab.relate({&a}, {&b}));
        REQUIRE(bc.relate({&b}, {&c}));
#if 0
        SECTION("Travel by all.") {
            MyTravel travel;

            travel.travel(&b, TRAVEL_BY_ALL);

            REQUIRE(travel.objs.size() == 3);
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &a) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &b) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &c) != travel.objs.end());

            REQUIRE(travel.rlts.size() == 2);
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &ab) != travel.rlts.end());
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &bc) != travel.rlts.end());
        }
#endif
        SECTION("Travel by from.") {
            MyTravel travel;

            travel.travel(&b, TRAVEL_BY_FROM);
            travel.print();

            REQUIRE(travel.objs.size() == 2);
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &b) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &c) != travel.objs.end());

            REQUIRE(travel.rlts.size() == 1);
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &bc) != travel.rlts.end());
        }

        SECTION("Travel by to.") {
            MyTravel travel;

            travel.travel(&a, TRAVEL_BY_TO);
            travel.print();

            REQUIRE(travel.objs.size() == 2);
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &b) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &a) != travel.objs.end());

            REQUIRE(travel.rlts.size() == 1);
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &ab) != travel.rlts.end());
        }
    }

    /**
     * 分析一个公式。
     */
    SECTION("equation.") {
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

        /**
         * 遍历某个对象相关的关系和对象。
         */
        SECTION("Travel by all.") {
            MyTravel travel;

            travel.travel(&b, TRAVEL_BY_ALL);

            REQUIRE(travel.objs.size() == 6);
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &a) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &b) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &c) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &v_2) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &sum) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &quotient) != travel.objs.end());

            REQUIRE(travel.rlts.size() == 3);
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &plus) != travel.rlts.end());
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &devide) != travel.rlts.end());
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &equal) != travel.rlts.end());
        }

        SECTION("Travel by from.") {
            MyTravel travel;

            travel.travel(&a, TRAVEL_BY_FROM);

            REQUIRE(travel.objs.size() == 6);
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &a) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &b) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &c) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &v_2) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &sum) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &quotient) != travel.objs.end());

            REQUIRE(travel.rlts.size() == 3);
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &plus) != travel.rlts.end());
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &devide) != travel.rlts.end());
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &equal) != travel.rlts.end());
        }

        SECTION("Travel by to.") {
            MyTravel travel;

            travel.travel(&c, TRAVEL_BY_TO);

            REQUIRE(travel.objs.size() == 6);
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &a) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &b) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &c) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &v_2) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &sum) != travel.objs.end());
            REQUIRE(std::find(travel.objs.begin(), travel.objs.end(), &quotient) != travel.objs.end());

            REQUIRE(travel.rlts.size() == 3);
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &plus) != travel.rlts.end());
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &devide) != travel.rlts.end());
            REQUIRE(std::find(travel.rlts.begin(), travel.rlts.end(), &equal) != travel.rlts.end());
        }
    }

}