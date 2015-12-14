#ifndef __SUBJECT_OBSERVER_H__
#define __SUBJECT_OBSERVER_H__

/**
 * 实现了提交者-观察者模式。
 * 和目前的其他实现都是独立的，可以用在其他地方。
 */

#include <list>

using namespace std;

/**
 * [接口]监视者
 * 监视其他对象发生变化的对象。
 */
class RObserver {
private:
protected:
public:
	// 子类必须实现。
	virtual void on_notify(void *pdata) = 0;
};

/**
 * 被监视的对象。
 * 当发生了变化后，通知监视它的所有对象。
 */
class RSubject {

private:

protected:
	/**
	 * 监视这个对象的所有监视者。
	 */
	list<RObserver *> observers;
	
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
	bool find_observer(RObserver * observer);
	
	/**
	 * 注册回调事件，当发生了变化后，就调用。
	 */
	bool register_observer(RObserver * observer);
	
	/**
	 * 删除监视函数。
	 */
	bool unregister_observer(RObserver * observer);
};

#endif // __SUBJECT_OBSERVER_H__
