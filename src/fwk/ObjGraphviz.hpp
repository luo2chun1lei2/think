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
    
    virtual bool begin_notify();
    virtual bool notify(Object *obj);
    virtual bool end_notify();

protected:
    Graphviz * graphviz;

    std::vector<Object *> notified_objects;
    std::vector<Relation *> notified_relations;

    std::map<Object *, Agnode_t *> obj_nodes;
    //std::map<Relation *, Agedge_t *> rlt_edges;

private:
};