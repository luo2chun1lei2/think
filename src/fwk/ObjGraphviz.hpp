#pragma once

#include <core/Object.hpp>

#include <vector>
#include <map>

#include <misc/Graphviz.hpp>

/**
 * 显示OR-Net为Graphviz。
 */
class ObjGraphviz : public Object
{
public:
    ObjGraphviz(const std::string name);
    virtual ~ObjGraphviz();

    ///////////////////////////////////////////////////////
    // 根据通知，同步
    
    // 通知开始
    virtual bool begin_notify();
    // 通知都有哪些对象。
    virtual bool notify(Object *obj);
    // 通知结束，绘制并显示结果。
    virtual bool end_notify();

protected:
    Graphviz * graphviz;

    std::vector<Object *> notified_objects;
    std::vector<Relation *> notified_relations;

    std::map<Object *, Agnode_t *> obj_nodes;
    //std::map<Relation *, Agedge_t *> rlt_edges;

private:
};