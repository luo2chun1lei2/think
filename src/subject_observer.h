#ifndef __SUBJECT_OBSERVER_H__
#define __SUBJECT_OBSERVER_H__

/**
 * 实现了提交者-观察者模式。
 * 和目前的其他实现都是独立的，可以用在其他地方。
 */

#include <list>

using namespace std;

class RSubject;

/**
 * [接口]监视者
 * 监视其他对象发生变化的对象。
 */
class RObserver {
private:
protected:
public:
	RObserver() {}
	
	/**
	 * TODO
	 * 在此方法中，需要将自己从Subject中反注册，不过这些Subject都有哪些，
	 * 根据每个实现的不同而不同，无法用一个通用的集合管理。
	 */
	virtual ~RObserver() {
		printf("~RObserver %p\n", this);
	}

	/**
	 * [子类实现]
	 * 当观察的对象发生变化后，这个方法就会被调用，然后此对象对此做出对应的处理。
	 */
	virtual void on_notify(RSubject * subject) = 0;
};

/////////////////////////////////////////////////

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
	bool raise_changed();

public:
	/**
	 * 构造方法。
	 */
	RSubject();
	
	/**
	 *
	 */
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
