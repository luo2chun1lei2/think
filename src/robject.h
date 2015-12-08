#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <list>
#include <string>

#include "subject_observer.h"

using namespace std;

/**
 * 每个对象具有的属性。
 * 当属性发生了改变后，就发出通知。
 */
class RProperty : public RSubject
{
private:
protected:
	string name;
public:
	RProperty(const string name) { this->name = name;}
	virtual ~RProperty() {}
	
	string get_name() { return name; }
};

/**
 * 最基本的对象类。
 * 当对象发生变化后，需要让另外的一个对象发生变化。
 */
class RObject {
private:
protected:
	// 每个对象的属性列表。
	list<RProperty *> properties;
	
public:
	RObject();
	virtual ~RObject();
	
	virtual bool find_property(const string name);
	virtual bool add_property(RProperty * pproperty);
};

/////////////////////////////
class RRelation {
private:
protected:
public:
	RRelation() {}
	virtual ~RRelation() {}
};

/////////////////////////////

class RGlobal {
private:
protected:
	list<RObject *> objs;
	list<RRelation *> relations;
	
public:
	RGlobal() {}
	
	virtual void add(RObject * obj) {
		objs.push_back(obj);
	}
	
	virtual void del(RObject * obj) {
		objs.remove(obj);
	}
		
	virtual void add(RRelation * rel) {
		relations.push_back(rel);
	}
	
	virtual void del(RRelation * rel) {
		relations.remove(rel);
	}
	
	virtual ~RGlobal() {}
};

#endif //__CONTAINER_H__

