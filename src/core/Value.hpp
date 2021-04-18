#pragma once

// 需要支持C++17.
#include <string>
#include <variant>

class Value {
public:
    typedef std::variant<int, double, std::string> Variant;
    typedef uint32_t Type;

    const static Type TYPE_NONE = 0;
    const static Type TYPE_INT = 1;
    const static Type TYPE_DOUBLE = 2;
    const static Type TYPE_STR = 3;

    Value() {
        this->type = TYPE_NONE;
    }

    Value(int v) {
        set_var(v);
    }

    Value(double v) {
        set_var(v);
    }

    Value(const std::string v) {
        set_var(v);
    }

    virtual ~Value() {
    }

    Type get_type() {
        return type;
    }

    void set_type(Type type) {
        this->type = type;
    }

    Variant get_var() {
        return var;
    }

    void set_var(Variant var) {
        this->var = var;
    }

    Value &operator=(const Value &other) {
        if (this == &other)
            return *this;

        this->type = other.type;
        this->var = other.var;

        return *this;
    }

protected:
    static Type type;
    Variant var;

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