#pragma once

#include <core/Object.hpp>

#include <string>

#include <stdio.h>

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
private:
};
