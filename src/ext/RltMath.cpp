#include <ext/RltMath.hpp>

#include <misc/Misc.hpp>

using namespace std;

///////////////////////////////////////////////////////////

RltPlus::RltPlus(const std::string name)
    : Relation(name) {
}

RltPlus::~RltPlus() {
}

bool RltPlus::perform() {
    /* TODO: Plus就按照严格的数学语法来进行，而不是搞一个集合的和。
    for (Object *obj : this->objects) {
        Value v = obj->get_value();
        // LOGE("%d + %d\n", this->value.get_int(), v.get_int());
        this->value += v;
    }
    */
    if (this->objects.size() != 2) {
        return false;
    }

    this->value = objects[0]->get_value() + objects[1]->get_value();

    return true;
}

void RltPlus::set_value(Value value) {
    // Cannot set value !
}

///////////////////////////////////////////////////////////

RltMinus::RltMinus(const std::string name)
    : Relation(name) {
}

RltMinus::~RltMinus() {
}

bool RltMinus::perform() {
    
    if (this->objects.size() != 2) {
        return false;
    }

    this->value = objects[0]->get_value() - objects[1]->get_value();

    return true;
}

void RltMinus::set_value(Value value) {
    // Cannot set value !
}

///////////////////////////////////////////////////////////

RltDevide::RltDevide(const std::string name)
    : Relation(name) {
}

RltDevide::~RltDevide() {
}

bool RltDevide::perform() {
    if (this->objects.size() != 2) {
        return false;
    }

    this->value = objects[0]->get_value() / objects[1]->get_value();

    return true;
}

void RltDevide::set_value(Value value) {
    // Cannot set value !
}

///////////////////////////////////////////////////////////

RltMultiple::RltMultiple(const std::string name)
    : Relation(name) {
}

RltMultiple::~RltMultiple() {
}

bool RltMultiple::perform() {
    if (this->objects.size() != 2) {
        return false;
    }

    this->value = objects[0]->get_value() * objects[1]->get_value();

    return true;
}

void RltMultiple::set_value(Value value) {
    // Cannot set value !
}

///////////////////////////////////////////////////////////