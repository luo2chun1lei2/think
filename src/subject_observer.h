#ifndef __SUBJECT_OBSERVER_H__
#define __SUBJECT_OBSERVER_H__

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

#endif // __SUBJECT_OBSERVER_H__