#include "robject.h"

RSubject::RSubject()
{
}

RSubject::~RSubject()
{
}

bool RSubject::find_observer(IObserver * observer)
{
	list<IObserver *>::iterator iter;
	for(iter = observers.begin(); iter != observers.end(); iter ++) {
		if( *iter == observer) {
			return true;
		}
	}
	return false;
}

bool RSubject::register_observer(IObserver * observer)
{
	if( find_observer(observer) ) {
		// 已经添加，就不再需要加入。
		return true;
	}
	
	observers.push_back(observer);
	
	return true;
}

bool RSubject::unregister_observer(IObserver * observer)
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

bool RSubject::raise_changed(void * pdata)
{
	list<IObserver *>::iterator iter;
	for(iter = observers.begin(); iter != observers.end(); iter ++) {
		(*iter)->on_notify(pdata);
	}
	return true;
}

////////////////////////////////////////

RObject::RObject()
{
}

RObject::~RObject()
{
}

bool RObject::find_property(const string name)
{
	return false;
}

bool RObject::add_property(RProperty * pproperty) 
{
	if(find_property(pproperty->get_name())) {
		// 同名属性已经设置
		return false;
	}
	
	properties.push_back(pproperty);
	
	return true;
}
