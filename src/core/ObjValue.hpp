#pragma once

#include <core/Object.hpp>
#include <core/Value.hpp>

class InterfaceValue : public Interface {
public:
    virtual Value get_value() = 0;
    virtual void set_value(Value value) = 0;
};

#define AsValue(instance)  dynamic_cast<InterfaceValue *>((instance)->interfaces()->get_impl("IValue"))

/**
 * 带有值的对象。
 * 【无法将一个值作为一个特殊的东西，那么就只能是一种对象了。】
 * TODO: 有什么用？Object就可以设置值了！
 * 1. 可以是任何值，比如字符串、整数、字符串等。
 */
class ObjValue : public Object {
public:
    class InnerValue : public InterfaceValue {
    public:
        InnerValue(ObjValue *obj_value) {
            _obj_value = obj_value;
        }
        virtual Value get_value() {
            return _obj_value->_value;
        }
        virtual void set_value(Value value) {
            _obj_value->_value = value;
        }

    protected:
        ObjValue *_obj_value;
    };

    ObjValue(const std::string name);
    virtual ~ObjValue();

protected:
    std::string _name;

protected:
    Value _value;

private:
};