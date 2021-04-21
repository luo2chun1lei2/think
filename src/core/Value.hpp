#pragma once

// 需要支持C++17.
#include <string>
#include <variant>

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
    Value(double v) ;
    Value(const std::string v);

    Type get_type() const;
    /* 不能设置类型！ 因为类型是设置具体值时决定的。 */
    //void set_type(Type type);

    virtual void set_var(Variant var);
    virtual void set_var(int var);
    virtual void set_var(double var);
    virtual void set_var(const std::string var);

    // TODO: 返回指针？
    Variant get_var() const;
    virtual int get_int() const;
    virtual double get_double() const;
    virtual std::string get_str() const;

    virtual const Value &operator+=(const Value &right);

protected:
    void init() {
        this->type = TYPE_NONE;
        this->var = nullptr;
    }

    Type type;
    Variant *var;

private:
};

/**
 * @brief 所有可以获取值的类的接口。
 *
 */
class IValue {
public:
    virtual void set_value(Value value) = 0;
    virtual Value get_value() = 0;
    /*
        virtual VarType get_value_type() = 0;

        virtual void set_value(int value) = 0;
        virtual int get_value_as_int() = 0;

        virtual void set_value(const std::string value) = 0;
        virtual std::string get_value_as_str() = 0;

        virtual void set_value(double value) = 0;
        virtual double get_value_as_double() = 0;
    */
};