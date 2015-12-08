#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <list>
#include <string>

using namespace std;

/////////////////////////////

/**
 * 接口：当发生变化后，通知实现这个接口的对象。
 */
class IObserver {
private:
protected:
public:
	// 子类必须实现。
	// TODO:可能会监视很多的对象，用这一个方法是无法区分的。
	virtual void on_notify(void *pdata) = 0;
};

/**
 * 当对象发生变化后，需要让另外的一个对象发生变化。
 */
class RSubject {

private:

protected:
	list<IObserver *> observers;
	
	/**
	 * 当发生了变化后，可以调用这个函数，通知所有的监视者。
	 */
	bool raise_changed(void * pdata);

public:
	RSubject();
	virtual ~RSubject();
	
	/**
	 * 寻找监视器是否已经注册。
	 */
	bool find_observer(IObserver * observer);
	
	/**
	 * 注册回调事件，当发生了变化后，就调用。
	 */
	bool register_observer(IObserver * observer);
	
	/**
	 * 删除毁掉事件。
	 */
	bool unregister_observer(IObserver * observer);
};

/////////////////////////////

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

