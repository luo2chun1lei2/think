#include <ext/RltMath.hpp>

#include <misc/Misc.hpp>

using namespace std;

///////////////////////////////////////////////////////////

RltPlus::RltPlus(const std::string name)
    : Relation(name) {
}

RltPlus::~RltPlus() {
}

void RltPlus::set_value(Value value) {
    // Cannot set value !
}

bool RltPlus::can_perform(const Object *pobj) const {
    return false;
}

vector<Object *> RltPlus::get_objs_need_value() const {
    vector<Object *> found;

    if (this->objects.size() != 2) {
        throw exception();
    }

    if (objects[0]->get_value().get_type() == Value::TYPE_NONE) {
        found.push_back(objects[0]);
    }

    if (objects[1]->get_value().get_type() == Value::TYPE_NONE) {
        found.push_back(objects[1]);
    }

    return found;
}

bool RltPlus::perform(std::vector<Object *> &need_objs) {
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

///////////////////////////////////////////////////////////

RltMinus::RltMinus(const std::string name)
    : Relation(name) {
}

RltMinus::~RltMinus() {
}

bool RltMinus::perform(std::vector<Object *> &need_objs) {

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

void RltDevide::set_value(Value value) {
    // Cannot set value !
}

bool RltDevide::can_perform(const Object *pobj) const {
    return false;
}

vector<Object *> RltDevide::get_objs_need_value() const {
    vector<Object *> found;

    if (this->objects.size() != 2) {
        throw exception();
    }

    if (objects[0]->get_value().get_type() == Value::TYPE_NONE) {
        found.push_back(objects[0]);
    }

    if (objects[1]->get_value().get_type() == Value::TYPE_NONE) {
        found.push_back(objects[1]);
    }

    return found;
}

bool RltDevide::perform(std::vector<Object *> &need_objs) {
    if (this->objects.size() != 2) {
        return false;
    }

    this->value = objects[0]->get_value() / objects[1]->get_value();

    return true;
}

///////////////////////////////////////////////////////////

RltMultiple::RltMultiple(const std::string name)
    : Relation(name) {
}

RltMultiple::~RltMultiple() {
}

bool RltMultiple::perform(std::vector<Object *> &need_objs) {
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

RltEqual::RltEqual(const std::string name)
    : Relation(name) {
}

RltEqual::~RltEqual() {
}

void RltEqual::set_value(Value value) {
    // Cannot set value !
}

bool RltEqual::can_perform(const Object *pobj) const {
    if (this->objects.size() != 2) {
        throw exception();
    }

    if (objects[0] == pobj) {
        return true;
    } else {
        return false;
    }
}

vector<Object *> RltEqual::get_objs_need_value() const {
    vector<Object *> found;

    if (this->objects.size() != 2) {
        throw exception();
    }

    if (objects[1]->get_value().get_type() == Value::TYPE_NONE) {
        found.push_back(objects[1]);
    }

    return found;
}

bool RltEqual::perform(std::vector<Object *> &need_objs) {
    if (this->objects.size() != 2) {
        return false;
    }

    objects[0]->set_value(objects[1]->get_value());

    return true;
}