#ifndef __ROBJECT_H__
#define __ROBJECT_H__

/**
 * Relation的基本模型。
 */

#include <list>
#include <string>

#include <cstdio>

#include "subject_observer.h"
#include "rdata.h"

using namespace std;

/*
class RObject : public RSubject {
private:
protected:
public:
};
*/

#if 0
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
#endif

/**
 * 最基本的对象类。
 * set_value/get_value利用RData进行数据传递（应该是数据备份）
 */
class RObject : public RSubject, public RObserver
{
private:
protected:
	// 每个对象的属性列表。
	//list<RProperty *> properties;
	
	RData * pdata;
	
public:
	RObject();
	virtual ~RObject();
	
	// TODO 参数传递是否不应该用指针传递，而用赋值传递，这样避免数据被其他地方修改，用“右值移动”？
	virtual void set_value(RData * pdata) {
		this->pdata = pdata;
		raise_changed();
	}
	
	virtual RData * get_value() {
		return pdata; 
	}
	
	virtual void on_notify(RSubject * subject) {
		printf("get message.\n");
	}
	
	//virtual bool find_property(const string name);
	//virtual bool add_property(RProperty * pproperty);
};

/////////////////////////////
/**
 * 关系也算是一个对象，所以在关系上也可以加入关系。
 * 建立对象上的关系，在对象上就是加入了一个属性，
 * 而关系则是独立的。
 */
class RRelation : public RObject
{
private:
protected:
	RObject * poutput;

public:
	// TODO 初始化需要加入几个对象？无法确定吗？在子类完成？
	// 一元关系存在吗？
	// 一定是二元关系吗？其他多元关系都用二元关系组成？
	RRelation() {}
	virtual ~RRelation() {
		printf("~RRelation %p\n", this);
	}
	
	virtual void set_outer(RObject * outer) {
		this->poutput = outer;
	}
};

/////////////////////////////
/*
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
	
	virtual void info_objects() {
		// 打印所有的对象的信息。
	}
	
	virtual void info_relations() {
		// 打印所有的关系的信息。
	}
	
	virtual ~RGlobal() {}
};
*/
#endif //__ROBJECT_H__
