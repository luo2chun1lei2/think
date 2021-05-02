#pragma once

#include <core/Object.hpp>

#include <ext/Travel.hpp>

class IPerform {
public:
    virtual bool perform(Object *pobj) = 0;
};

/**
 * 通过一轮一轮的循环处理所有的Relation，直到获得对象值，或者OR-Net无改变。
 */
class PerformRound : public IPerform {
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

/**
 * 通过分析对象相关的关系，找到关联影响树后，进行处理。
 * 找到*被影响*【不是影响的顺序！】顺序后，开始处理影响，效率高。
 */
class PerformAffectedTree : IPerform {
public:
    PerformAffectedTree();
    virtual ~PerformAffectedTree();

    /**
     * 根据pobj的关联关系，运转得到pobj的状态。
     */
    virtual bool perform(Object *pobj);

protected:
    // TODO: need ？
    // If return false, travel will be broken.
    virtual bool on_meet_obj(Object *pobj);
    // If return false, travel will be broken.
    virtual bool on_meet_rlt(Relation *prlt);

private:
};

