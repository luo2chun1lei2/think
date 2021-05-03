#pragma once

// 需要支持C++17.
#include <string>
#include <variant>

/**
 * 可变值，允许设定各种不同类型的值。
 * 1. 设定时记录值的类型，且可以取出来。
 * 2. 可以进行数学运算。
 */
class Value {
public:
    typedef std::variant<int, double, std::string> Variant;
    typedef uint32_t Type;

    const static Type TYPE_NONE;
    const static Type TYPE_INT;
    const static Type TYPE_DOUBLE;
    const static Type TYPE_STR;

    Value();
    Value(const Value &v);
    virtual Value &operator=(const Value &right);

    virtual ~Value();

    Value(int v);
    Value(double v);
    Value(const std::string v);

    Type get_type() const;

    /* 不能设置类型！ 因为类型是设置具体值时决定的。 */
    // void set_type(Type type);

    virtual void set_var(Variant var);
    virtual void set_var(int var);
    virtual void set_var(double var);
    virtual void set_var(const std::string var);

    Variant get_var() const;
    virtual int get_int() const;
    virtual double get_double() const;
    virtual std::string get_str() const;

    ///////////////////////////////////////////////////////
    // 数学运算。

    friend void var_to_digit(const Value &value, Value::Type & type, Value::Variant **var);

    virtual const Value &operator+=(const Value &right);
    virtual const Value &operator-=(const Value &right);
    virtual const Value &operator*=(const Value &right);
    virtual const Value &operator/=(const Value &right);

    friend Value operator+(const Value &lhs, const Value &rhs);
    friend Value operator-(const Value &lhs, const Value &rhs);
    friend Value operator*(const Value &lhs, const Value &rhs);
    friend Value operator/(const Value &lhs, const Value &rhs);

protected:
    void init();

    Type type;
    Variant *var;

private:
};

void var_to_digit(const Value &value, Value::Type & type, Value::Variant **var);
Value operator+(const Value &lhs, const Value &rhs);
Value operator-(const Value &lhs, const Value &rhs);
Value operator*(const Value &lhs, const Value &rhs);
Value operator/(const Value &lhs, const Value &rhs);


/**
 * @brief 所有可以获取值的类的接口。
 * 必须可以设置值和获取值。但是不应要两个都支持。
 */
class IValue {
public:
    virtual void set_value(Value value) = 0;
    virtual Value get_value() = 0;
};