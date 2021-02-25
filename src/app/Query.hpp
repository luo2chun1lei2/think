#pragma once

#include <string>

#include <Model.hpp>

/**
 * 针对模型进行查询
 * TODO: 之后也做成Element。
 */
class Query
{
public:
    Query(const std::string name);
    virtual ~Query();

    // 根据表达式，得到元素。 TODO:以后扩展后，也许得到的是值！
    Element * query(const Model *model, const std::string expr);

protected:
    std::string name;
private:
};