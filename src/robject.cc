#include "robject.h"

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
