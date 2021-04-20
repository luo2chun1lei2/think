#pragma once

/**
 * @brief 数学计算公式相关的关系都放在这里。
 * 
 */

#include <string>

#include <core/Relation.hpp>

class RltAdd : public Relation
{
public:
    RltAdd(const std::string name);
    virtual ~RltAdd();

    virtual Value get_value();
    virtual void set_value(Value value);

    virtual bool perform();

protected:

private:

};
