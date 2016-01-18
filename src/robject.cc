#include "robject.h"

RObject::RObject()
{
}

RObject::~RObject()
{
	printf("~RObject %p\n", this);
}

/**
 * 根据指定的名字，找到对应的Relation。
 * \return NULL:没有找到，其他：RRelation*
 */
RRelation * RObject::findRelation(const string name)
{
	Relations::iterator found = relations.find(name);
	
	if(found == relations.end()) {
		return NULL;
	}
	
	return found->second;
}

/**
 * 加入Relation。
 * \return true:加入，false:失败。
 */
bool RObject::addRelation(const string name, RRelation * rel)
{
	auto rlt = relations.emplace(make_pair(name, rel));
	return rlt.second;
}

/**
 * \brief 删除指定名字的关系。
 * \return NULL:没有找到，其他，被删除的Relation。
 */
RRelation * RObject::delRelation(const string name)
{
	Relations::iterator found = relations.find(name);
	
	if(found == relations.end()) {
		return NULL;
	}
	
	RRelation * p = found->second;
	relations.erase(found);
	
	return p;
}
