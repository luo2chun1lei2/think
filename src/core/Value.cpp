#include <core/Value.hpp>

const Value::Type Value::TYPE_NONE = 0;
const Value::Type Value::TYPE_INT = 1;
const Value::Type Value::TYPE_DOUBLE = 2;
const Value::Type Value::TYPE_STR = 3;

Value::Value() {
    init();
}

Value::Value(int v) {
    init();
    set_var(v);
}

Value::Value(double v) {
    init();
    set_var(v);
}

Value::Value(const std::string v) {
    init();
    set_var(v);
}

Value::Value(const Value &v) {
    init();
    this->type = v.type;
    if (v.var) {
        this->var = new Variant(*v.var);
    } else {
        this->var = nullptr;
    }
}

Value::~Value() {
    // TODO: 遇到崩溃，先删除！
    delete this->var;
}

Value::Type Value::get_type() const {
    return type;
}

/* 不能设置类型！
void Value::set_type(Value::Type type) {
    this->type = type;
}
*/

// TODO: 返回指针？
Value::Variant Value::get_var() const {
    if (var == nullptr) {
        return Variant();
    } else {
        return *var;
    }
}

void Value::set_var(int var) {
    delete this->var;

    this->type = TYPE_INT;
    this->var = new Variant(var);
}

void Value::set_var(double var) {
    delete this->var;

    this->type = TYPE_DOUBLE;
    this->var = new Variant(var);
}

void Value::set_var(const std::string var) {
    delete this->var;

    this->type = TYPE_STR;
    this->var = new Variant(var);
}

void Value::set_var(Value::Variant var) {
    if (!this->var) {
        this->var = new Variant();
    }
    *this->var = var;
}

int Value::get_int() const {
    return std::get<int>(*var);
}

double Value::get_double() const {
    return std::get<double>(*var);
}

std::string Value::get_str() const {
    return std::get<std::string>(*var);
}

Value &Value::operator=(const Value &other) {
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

const Value &Value::operator+=(const Value &right) {

    if (right.get_type() < TYPE_NONE || right.get_type() > TYPE_STR) {
        // ERROR
    }

    if (get_type() < TYPE_NONE || get_type() > TYPE_STR) {
        // ERROR
    }

    switch (get_type()) {
        case TYPE_NONE: {
            // TODO: 这里的策略还需要再商量。
            this->type = right.get_type();
            this->var = new Variant(right.get_var());
        }

        break;
        case TYPE_INT: {
            switch (right.get_type()) {
                case TYPE_NONE:
                    // do nothing
                    break;
                case TYPE_INT:
                    this->var = new Variant(right.get_int() + this->get_int());
                    break;
                case TYPE_DOUBLE:
                    this->type = TYPE_DOUBLE;
                    this->var = new Variant(right.get_int() + get_int());
                    break;
                case TYPE_STR:
                    //??
                    break;
            }
        } break;

        case TYPE_DOUBLE: {
            switch (right.get_type()) {
                case TYPE_NONE:
                    // do nothing
                    break;
                case TYPE_INT:
                    this->var = new Variant(right.get_int() + get_double());
                    break;
                case TYPE_DOUBLE:
                    this->var = new Variant(right.get_double() + get_double());
                    break;
                case TYPE_STR:
                    //??
                    break;
            }
        } break;

        case TYPE_STR: {
            switch (right.get_type()) {
                case TYPE_NONE:
                    //??
                    break;
                case TYPE_INT:
                    //??
                    break;
                case TYPE_DOUBLE:
                    //??
                    break;
                case TYPE_STR:
                    //??
                    break;
            }
        } break;
    }

    return *this;
}