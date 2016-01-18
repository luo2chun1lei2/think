#ifndef __ROBJECT_H__
#define __ROBJECT_H__

/**
 * 关系的基本元素。
 */

#include <list>
#include <map>
#include <string>

#include <cstdio>

#include "subject_observer.h"
#include "rdata.h"

using namespace std;

// Relation Class.
class RRelation;

/**
 * 所有对象的基类。
 * 拥有的接口：
 * Subject: 可以被监听
 * Value: 可以调用setValue/getValue函数：因为
 */
class RObject : public RSubject, public BValue
{
private:
protected:
    /**
	 * 名字是放在Relation中，还是放在外面？ 
	 * Relation会被多方使用，会具有不同的名字，所以必须放在外面。但是可以具有自己缺省的名字。
     */
	typedef map<string, RRelation *> Relations;
	
	/** 
	 * 具有的所有关系
	 */ 
	Relations relations;
	
public:
	RObject();
	virtual ~RObject();

	virtual void setValue(BData data) {
		BValue::setValue(data);
		raiseChanged();
	}
	
	/**
	 * 根据指定的名字，找到对应的Relation。
	 * \return NULL:没有找到，其他：RRelation*
	 */
	virtual RRelation * findRelation(const string name);
	
	/**
	 * 加入Relation。
	 * \return true:加入，false:失败。
	 */
	virtual bool addRelation(const string name, RRelation * rel);
	
	/**
	 * \brief 删除指定名字的关系。
	 * \return NULL:没有找到，其他，被删除的Relation。
	 */
	virtual RRelation * delRelation(const string name);
	
};

/////////////////////////////

/**
 * 维持对象与对象（可以有多个，多方关系）之间关系的类。
 * 目前的实现是：当其中对象发生了变化后，关系类就维持对象之间的关系。
 * 另外，关系本身也是一个对象，它也可以被监视，和维持与其他对象之间的关系。
 * TODO :目前没有找到关系的共通接口。
 */
class RRelation : public RObject, public RObserver
{
private:

protected:

public:
	//TODO 子类通过不同的构造方法，构建自己的关系网。
	RRelation() {}
	
	virtual ~RRelation() {
		printf("~RRelation %p\n", this);
	}
};

/**
 * 只有一个影响目标的关系。
 * TODO 此对象也可以伪装成一个有值的对象，比如加法，但是也可能就是有对应的影响对象，而不是本身就是影响对象，
 *   以上的思路还需要再思考。
 */
class RelOne : public RRelation
{
private:
protected:
	RObject * pTo;
	
public:
	virtual void setTo(RObject * obj) {
		this->pTo = obj;
	}
	
	virtual RObject * getTo() {
		return this->pTo;
	}
};

/////////////////////////////
/* TODO 这个还要吗？
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
