#pragma once

#include <core/Object.hpp>
#include <core/Value.hpp>

/**
 * 带有值对象。
 * 可以是任何值，比如字符串/整数。
 * 基本的是字符串。
 */
class ObjValue : public Object
{
public:
    ObjValue(const std::string name);
	virtual ~ObjValue();

protected:
    
private:

};