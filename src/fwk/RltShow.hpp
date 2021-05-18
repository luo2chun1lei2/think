#pragma once

#include <core/Relation.hpp>

/**
 * Show会将 from 对象相关的 OR-Net 都发送给 to 对象。
 * to 对象必须支持接收 OR-Net 的信息。
 * 可以用来连接到 ObjGraphviz。
 * 
 * TODO: 反思，是否应该按照“遍历的方式”来设定另外的Relation？
 */
class RltShow : public Relation
{
public:
    RltShow(const std::string name);
    virtual ~RltShow();

    virtual bool perform();
protected:
private:
};