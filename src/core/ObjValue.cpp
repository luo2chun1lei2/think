#include <core/ObjValue.hpp>

using namespace std;

ObjValue::ObjValue(const std::string id)
    : Object(id) {
    _interfaces->add_impl("IValue", new InnerValue(this));
}

ObjValue::~ObjValue() {
}
