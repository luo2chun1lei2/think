#pragma once

#include <core/Object.hpp>
#include <core/Value.hpp>

/**
 * 带有值的对象。
 * TODO: 有什么用？Object就可以设置值了！
 * 1. 可以是任何值，比如字符串、整数、字符串等。
 */
class ObjValue : public Object
{
public:
    ObjValue(const std::string name);
	virtual ~ObjValue();

protected:
    
private:

};