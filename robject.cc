#include "robject.h"

RObject::RObject()
{
}

RObject::~RObject()
{
}

bool RObject::find_observer(IObserver * observer)
{
	list<IObserver *>::iterator iter;
	for(iter = observers.begin(); iter != observers.end(); iter ++) {
		if( *iter == observer) {
			return true;
		}
	}
	return false;
}

bool RObject::register_observer(IObserver * observer)
{
	if( find_observer(observer) ) {
		// 已经添加，就不再需要加入。
		return true;
	}
	
	observers.push_back(observer);
	
	return true;
}

bool RObject::unregister_observer(IObserver * observer)
{
	if( ! find_observer(observer) ) {
		// 没有加入，就不用删除。
		return true;
	}
	
	observers.remove_if(
		[observer](IObserver * & o) -> bool
			{return o == observer;}
	);
	
	return true;
}

bool RObject::raise_changed(void * pdata)
{
	list<IObserver *>::iterator iter;
	for(iter = observers.begin(); iter != observers.end(); iter ++) {
		(*iter)->on_notify(pdata);
	}
	return true;
}

