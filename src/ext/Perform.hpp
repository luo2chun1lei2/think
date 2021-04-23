#pragma once

#include <core/Object.hpp>

#include <ext/Travel.hpp>

/**
 * 通过一轮一轮的循环处理所有的Relation，直到获得对象值，或者OR-Net无改变。
 */
class PerformRound {
public:
    PerformRound(int max_round);
    virtual ~PerformRound();

    /**
     * 根据pobj的关联关系，运转得到pobj的状态。
     */
    virtual bool perform(Object *pobj);

protected:

    class MyTravel : public Travel {
        public:
            MyTravel(bool log);

            bool is_end();

            virtual bool travel(Object *pobj);

        protected:
            virtual bool on_meet_obj(Object *pobj);

            virtual bool on_meet_rlt(Relation *prlt);

            std::vector<Object *> last_oks;
            std::vector<Object *> cur_oks;

            Object *target;
            bool end;

        private:
    };

    int max_round;

private:
};

class Perform {
public:
    Perform();
    virtual ~Perform();

    /**
     * 根据pobj的关联关系，运转得到pobj的状态。
     */
    virtual bool perform(Object *pobj);

protected:
    // If return false, travel will be broken.
    virtual bool on_meet_obj(Object *pobj);
    // If return false, travel will be broken.
    virtual bool on_meet_rlt(Relation *prlt);

private:
};

