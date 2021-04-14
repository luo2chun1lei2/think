#include <Value.hpp>

using namespace std;

Value::Value(const std::string name)
    : Object(name) {
    value_type = VAR_TYPE_NONE;
    value = nullptr;
}

Value::~Value() {
    delete this->value;
}

VarType Value::get_value_type() {
    return value_type;
}

void Value::set_value(int value) {
    delete this->value;

    value_type = VAR_TYPE_INT;
    this->value = new Variant(value);
}

int Value::get_value_as_int() {
    return std::get<int>(*value);
}

void Value::set_value(const std::string value) {
    delete this->value;

    value_type = VAR_TYPE_STR;
    this->value = new Variant(value);
}

std::string Value::get_value_as_str() {
    return std::get<std::string>(*value);
}

void Value::set_value(double value) {
    delete this->value;

    value_type = VAR_TYPE_DOUBLE;
    this->value = new Variant(value);
}

double Value::get_value_as_double() {
    return std::get<double>(*value);
}
