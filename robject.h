#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <list>

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
 * 最基本的对象类。
 * 当对象发生变化后，需要让另外的一个对象发生变化。
 */
class RObject {
private:
protected:
public:
	RObject();
	virtual ~RObject();
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

