#pragma once

#include <Object.hpp>

// 需要支持C++17.
#include <variant>

enum VarType
{
VAR_TYPE_NONE = 0,
VAR_TYPE_INT = 1,
VAR_TYPE_STR = 2,
VAR_TYPE_DOUBLE = 3,
};

/**
 * 带有值对象。
 * 可以是任何值，比如字符串/整数。
 * 基本的是字符串。
 */
class Value : public Object
{
public:
    Value(const std::string name);
	virtual ~Value();

    virtual VarType get_value_type();
    
    virtual void set_value(int value);
    virtual int get_value_as_int();

    virtual void set_value(const std::string value);
    virtual std::string get_value_as_str();

    virtual void set_value(double value);
    virtual double get_value_as_double();

protected:
    typedef std::variant<int, double, std::string> Variant;
    VarType value_type;
    Variant *value;
    
private:

};