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

    Value() {
        init();
    }

    Value(int v) {
        init();
        set_var(v);
    }

    Value(double v) {
        init();
        set_var(v);
    }

    Value(const std::string v) {
        init();
        set_var(v);
    }

    virtual ~Value() {
        //printf("-->%p\n", this->var);
        // TODO: 遇到崩溃，先删除！
        //delete this->var;
    }

    Type get_type() {
        return type;
    }

/* 不能设置类型！
    void set_type(Type type) {
        this->type = type;
    }
    */

   // TODO: 返回指针？
    Variant get_var() {
        if (var == nullptr) {
            return Variant();
        } else {
            return *var;
        }
    }

    void set_var(int var) {
        delete this->var;

        this->type = TYPE_INT;
        this->var = new Variant(var);
    }

    void set_var(double var) {
        delete this->var;

        this->type = TYPE_DOUBLE;
        this->var = new Variant(var);
    }

    void set_var(const std::string var) {
        delete this->var;

        this->type = TYPE_STR;
        this->var = new Variant(var);
    }

/*
    void set_var(Variant var) {
        if(!this->var) {
            this->var = new Variant();
        }
        *this->var = var;
    } */

    virtual Value &operator=(const Value &other) {
        if (this == &other)
            return *this;

        this->type = other.type;
        if (other.var) {
            this->var = new Variant(*other.var);
        } else {
            this->var = nullptr;
        }

        return *this;
    }

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