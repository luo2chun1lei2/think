#include <ext/ObjValue.hpp>

using namespace std;

ObjValue::ObjValue(const std::string name)
    : Object(name) {
}

ObjValue::~ObjValue() {
}

// Value ObjValue::get_value() {
//     return value;
// }
// void ObjValue::set_value(Value value) {
//     this->value = value;
// }

/*
VarType ObjValue::get_value_type() {
    return value_type;
}

void ObjValue::set_value(int value) {
    delete this->value;

    value_type = VAR_TYPE_INT;
    this->value = new Variant(value);
}

int ObjValue::get_value_as_int() {
    return std::get<int>(*value);
}

void ObjValue::set_value(const std::string value) {
    delete this->value;

    value_type = VAR_TYPE_STR;
    this->value = new Variant(value);
}

std::string ObjValue::get_value_as_str() {
    return std::get<std::string>(*value);
}

void ObjValue::set_value(double value) {
    delete this->value;

    value_type = VAR_TYPE_DOUBLE;
    this->value = new Variant(value);
}

double ObjValue::get_value_as_double() {
    return std::get<double>(*value);
}
*/