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

    // virtual Value get_value();
    // virtual void set_value(Value value);

/*    
    virtual void set_value(int value);
    virtual int get_value_as_int();

    virtual void set_value(const std::string value);
    virtual std::string get_value_as_str();

    virtual void set_value(double value);
    virtual double get_value_as_double();
*/

protected:
    Value value;
    
private:

};