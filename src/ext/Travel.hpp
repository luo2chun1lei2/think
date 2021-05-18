#pragma once

#include <core/Object.hpp>

enum TravelMode
{
    // 对象的影响组(按照对象的from)
    TRAVEL_BY_FROM = 1,
    // 对象的被影响对象(按照对象的to)
    TRAVEL_BY_TO = 2,
    TRAVEL_BY_ALL = 3,
};

/**
 * 遍历指定的元素的相关所有关系和元素。
 * 主要用于通过遍历而直到有哪些对象和关系涉及到。
 * 
 * TODO: 主动影响相关性， 被动影响相关性、全部相关性。
 * 
 * TODO: 这里和Tree的算法重复。怎么进行合并？
 * Travel给RltShow用的，Tree是Perform用的。
 * Tree 用于生成关联Tree用。
 */
class Travel
{
public:
    Travel() {write_log = false;}
    Travel(bool log) {write_log = log;}
    virtual ~Travel() {}
    // 
    /**
     * @brief 这里算法是通过关联关系，遍历关系图。
     * 
     * @param pobj 
     * @return true 
     * @return false exit because travel has been broken. 
     */
    virtual bool travel(Object * pobj, TravelMode travel_mode = TRAVEL_BY_ALL);

protected:
    // If return false, travel will be broken.
    virtual bool on_meet_obj(Object * pobj) = 0;
    // If return false, travel will be broken.
    virtual bool on_meet_rlt(Relation * prlt) = 0;

    bool write_log;

private:

};