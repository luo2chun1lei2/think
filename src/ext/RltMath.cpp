#include <ext/RltMath.hpp>

#include <misc/Misc.hpp>

using namespace std;

///////////////////////////////////////////////////////////

RltMathOperation::RltMathOperation(const std::string name)
    : Relation(name) {
}
RltMathOperation::~RltMathOperation() {
}

void RltMathOperation::set_value(Value value) {
}

std::vector<Object *> RltMathOperation::get_objs_need_value() const {
    vector<Object *> found;

    if (this->objects.size() != 3) {
        throw exception();
    }

    if (objects[1]->get_value().get_type() == Value::TYPE_NONE) {
        found.push_back(objects[0]);
    }

    if (objects[2]->get_value().get_type() == Value::TYPE_NONE) {
        found.push_back(objects[1]);
    }

    return found;
}

///////////////////////////////////////////////////////////

RltPlus::RltPlus(const std::string name)
    : RltMathOperation(name) {
}

RltPlus::~RltPlus() {
}

bool RltPlus::can_perform(const Object *pobj) const {
    return false;
}

bool RltPlus::perform(std::vector<Object *> &need_objs) {
    /* TODO: Plus就按照严格的数学语法来进行，而不是搞一个集合的和。
    for (Object *obj : this->objects) {
        Value v = obj->get_value();
        // LOGE("%d + %d\n", this->value.get_int(), v.get_int());
        this->value += v;
    }
    */
    if (this->objects.size() != 3) {
        return false;
    }

    for (Object *obj : objects) {
        if (obj == objects[0]) {
            continue;
        }
        if (obj->get_value().get_type() == Value::TYPE_NONE) {
            return false;
        }
    }

    objects[0]->set_value(objects[1]->get_value() + objects[2]->get_value());

    return true;
}

///////////////////////////////////////////////////////////

RltMinus::RltMinus(const std::string name)
    : RltMathOperation(name) {
}

RltMinus::~RltMinus() {
}

bool RltMinus::perform(std::vector<Object *> &need_objs) {

    if (this->objects.size() != 3) {
        return false;
    }

    for (Object *obj : objects) {
        if (obj == objects[0]) {
            continue;
        }
        if (obj->get_value().get_type() == Value::TYPE_NONE) {
            return false;
        }
    }

    objects[0]->set_value(objects[1]->get_value() - objects[2]->get_value());

    return true;
}

///////////////////////////////////////////////////////////

RltDevide::RltDevide(const std::string name)
    : RltMathOperation(name) {
}

RltDevide::~RltDevide() {
}

bool RltDevide::can_perform(const Object *pobj) const {
    return false;
}

bool RltDevide::perform(std::vector<Object *> &need_objs) {
    if (this->objects.size() != 3) {
        return false;
    }

    for (Object *obj : objects) {
        if (obj == objects[0]) {
            continue;
        }
        if (obj->get_value().get_type() == Value::TYPE_NONE) {
            return false;
        }
    }

    objects[0]->set_value(objects[1]->get_value() / objects[2]->get_value());

    return true;
}

///////////////////////////////////////////////////////////

RltMultiple::RltMultiple(const std::string name)
    : RltMathOperation(name) {
}

RltMultiple::~RltMultiple() {
}

bool RltMultiple::perform(std::vector<Object *> &need_objs) {
    if (this->objects.size() != 3) {
        return false;
    }

    for (Object *obj : objects) {
        if (obj == objects[0]) {
            continue;
        }
        if (obj->get_value().get_type() == Value::TYPE_NONE) {
            return false;
        }
    }

    objects[0]->set_value(objects[1]->get_value() * objects[2]->get_value());

    return true;
}

///////////////////////////////////////////////////////////

RltEqual::RltEqual(const std::string name)
    : RltMathOperation(name) {
}

RltEqual::~RltEqual() {
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

    if (objects[1]->get_value().get_type() == Value::TYPE_NONE) {
        return false;
    }

    objects[0]->set_value(objects[1]->get_value());

    return true;
}