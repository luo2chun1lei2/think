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

    std::string query(const Model *model, const std::string expr);

protected:
    std::string name;
private:
};