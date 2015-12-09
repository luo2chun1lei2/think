#include "subject_observer.h"

RSubject::RSubject()
{
}

RSubject::~RSubject()
{
}

bool RSubject::find_observer(RObserver * observer)
{
	list<RObserver *>::iterator iter;
	for(iter = observers.begin(); iter != observers.end(); iter ++) {
		if( *iter == observer) {
			return true;
		}
	}
	return false;
}

bool RSubject::register_observer(RObserver * observer)
{
	if( find_observer(observer) ) {
		// 已经添加，就不再需要加入。
		return true;
	}
	
	observers.push_back(observer);
	
	return true;
}

bool RSubject::unregister_observer(RObserver * observer)
{
	if( ! find_observer(observer) ) {
		// 没有加入，就不用删除。
		return true;
	}
	
	observers.remove_if(
		[observer](RObserver * & o) -> bool
			{return o == observer;}
	);
	
	return true;
}

bool RSubject::raise_changed(void * pdata)
{
	list<RObserver *>::iterator iter;
	for(iter = observers.begin(); iter != observers.end(); iter ++) {
		(*iter)->on_notify(pdata);
	}
	return true;
}
