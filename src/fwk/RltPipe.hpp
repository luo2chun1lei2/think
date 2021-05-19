#pragma once

#include <stdio.h>

#include <string>

#include <core/Object.hpp>
#include <fwk/ILine.hpp>

/**
 * @brief 将From的一行一行的数据传递到To中。
 */
class RltPipeLine : public Relation
{
public:
    RltPipeLine(const std::string name);
    virtual ~RltPipeLine();
    virtual bool perform(std::vector<Object *> &need_objs);
protected:
    virtual bool exec_one(ILine * pline);
private:
};
