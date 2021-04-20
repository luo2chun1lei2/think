#include <ext/RltMath.hpp>

#include <misc/Misc.hpp>

using namespace std;

///////////////////////////////////////////////////////////

RltAdd::RltAdd(const std::string name)
    : Relation(name) {
}

RltAdd::~RltAdd() {
}

bool RltAdd::perform() {
    // 处理在 get_value 做，还是在get_value 做?
    for (Object *obj : this->objects) {
        Value v = obj->get_value();
        // LOGE("%d + %d\n", std::get<int>(this->value.get_var()), std::get<int>(v.get_var()));
        this->value += v;
    }

    return true;
}

Value RltAdd::get_value() {
    return this->value;
}

void RltAdd::set_value(Value value) {
    // Cannot set value !
}

///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////