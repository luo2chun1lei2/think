#pragma once

#include <core/Object.hpp>

/**
 * 遍历指定的元素。
 */
class Travel
{
public:
    Travel() {}
    virtual ~Travel() {}
    // If return false, exit because travel has been broken.
    virtual bool travel(Object * pobj);

protected:
    // If return fale, travel will be broken.
    virtual bool on_meet_obj(Object * pobj) = 0;
    // If return fale, travel will be broken.
    virtual bool on_meet_rlt(Relation * prlt) = 0;

private:

};