#pragma once

#include <core/Object.hpp>

/**
 * 遍历指定的元素。
 */
class Travel
{
public:
    Travel() {write_log = false;}
    Travel(bool log) {write_log = log;}
    virtual ~Travel() {}
    // If return false, exit because travel has been broken.
    virtual bool travel(Object * pobj);

protected:
    // If return false, travel will be broken.
    virtual bool on_meet_obj(Object * pobj) = 0;
    // If return false, travel will be broken.
    virtual bool on_meet_rlt(Relation * prlt) = 0;

    bool write_log;

private:

};