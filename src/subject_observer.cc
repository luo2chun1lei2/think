#include <cstdio>

#include "subject_observer.h"

/////////////////////////////////////////////////

RSubject::RSubject()
{
}

RSubject::~RSubject()
{
	printf("~RSubject %p\n", this);
}

bool RSubject::findObserver(RObserver * observer)
{
	list<RObserver *>::iterator iter;
	for(iter = observers.begin(); iter != observers.end(); iter ++) {
		if( *iter == observer) {
			return true;
		}
	}
	return false;
}

bool RSubject::registerObserver(RObserver * observer)
{
	if( findObserver(observer) ) {
		// 已经添加，就不再需要加入。
		return true;
	}
	
	printf("register message.\n");
	observers.push_back(observer);
	
	return true;
}

bool RSubject::unregisterObserver(RObserver * observer)
{
	if( ! findObserver(observer) ) {
		// 没有加入，就不用删除。
		return true;
	}
	
	observers.remove_if(
		[observer](RObserver * & o) -> bool
			{return o == observer;}
	);
	
	return true;
}

bool RSubject::raiseChanged()
{
	list<RObserver *>::iterator iter;
	for(iter = observers.begin(); iter != observers.end(); iter ++) {
		printf("send message.\n");
		(*iter)->onNotify(this);
	}
	return true;
}
