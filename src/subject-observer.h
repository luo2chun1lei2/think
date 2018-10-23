#pragma once

#include <list>

#include "value.h"

using namespace std;

//////////////////////////////////////////////////
// 注册和通知（Event)

class ESubject;

class EObserver
{
public:
	// 接受者需要知道来源，才能正确的处理多个内部元素的问题。
	virtual void update(ESubject * sub, VValue &value) = 0;
protected:	
private:
};

/**
 * 发送信息方。自身有改变通知观察者(Observer)。
 */
class ESubject
{
public:
	typedef list<EObserver *> obs_list_t;
	virtual void attach(EObserver * obs) {
		obs_list_t::iterator itr;
		for(itr = observers.begin(); itr != observers.end(); itr ++) {
			if ( *itr == obs ) {
				// already attached, so exit.
				return;
			}
		}
		observers.push_back(obs);
	}
	
	virtual void detach(EObserver *obs) {
		obs_list_t::iterator itr;
		
		for(itr = observers.begin(); itr != observers.end(); itr ++) {
			if ( *itr == obs ) {
				observers.erase(itr);
				break;
			}
		}
		
	}
	// 当subject发生变化后，通知所有的observer。
	virtual void notify(VValue &value) {
		obs_list_t::iterator itr;
		for(itr = observers.begin(); itr != observers.end(); itr ++) {
			(*itr)->update(this, value);
		}
	}
protected:
	list<EObserver *> observers;
private:
};