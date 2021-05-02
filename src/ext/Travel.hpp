#pragma once

#include <core/Object.hpp>

/**
 * 遍历指定的元素的相关所有关系和元素。
 * 主要用于通过遍历而直到有哪些对象和关系涉及到。
 * TODO: 这里和Tree的算法重复。怎么进行合并？
 */
class Travel
{
public:
    Travel() {write_log = false;}
    Travel(bool log) {write_log = log;}
    virtual ~Travel() {}
    // 
    /**
     * @brief 这里算法是通过关联关系，遍历关系图。顺序是先序。
     * 
     * @param pobj 
     * @return true 
     * @return false exit because travel has been broken. 
     */
    virtual bool travel(Object * pobj);

protected:
    // If return false, travel will be broken.
    virtual bool on_meet_obj(Object * pobj) = 0;
    // If return false, travel will be broken.
    virtual bool on_meet_rlt(Relation * prlt) = 0;

    bool write_log;

private:

};