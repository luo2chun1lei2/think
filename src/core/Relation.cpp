#include <core/Relation.hpp>

#include <initializer_list>

#include <misc/Misc.hpp>

using namespace std;

Relation::Relation(const std::string name)
    : Object(name) {
}

Relation::~Relation() {
}

bool Relation::relate(initializer_list<Object *> from_objs,
    initializer_list<Object *> to_objs) {

    for (auto beg = from_objs.begin(); beg != from_objs.end(); ++beg) {
        if (add_from_obj(*beg) == false) {
            LOGE("Cannot add object into relation.");
            return false;
        }
    }

    for (auto beg = to_objs.begin(); beg != to_objs.end(); ++beg) {
        if (add_to_obj(*beg) == false) {
            LOGE("Cannot add object into relation.");
            return false;
        }
    }

    return true;
}

bool Relation::relate(std::vector<Object *> from_objs, std::vector<Object *> to_objs) {
    for (auto beg = from_objs.begin(); beg != from_objs.end(); ++beg) {
        if (add_from_obj(*beg) == false) {
            LOGE("Cannot add object into relation.");
            return false;
        }
    }

    for (auto beg = to_objs.begin(); beg != to_objs.end(); ++beg) {
        if (add_to_obj(*beg) == false) {
            LOGE("Cannot add object into relation.");
            return false;
        }
    }

    return true;
}

size_t Relation::get_count_of_from_objs() {
    return _from_objs.size();
}

size_t Relation::get_count_of_to_objs() {
    return _to_objs.size();
}

Object *Relation::get_from_obj(uint32_t index) {
    return _from_objs[index];
}

Object *Relation::get_to_obj(uint32_t index) {
    return _to_objs[index];
}

const std::vector<Object *> &Relation::get_from_objs() const {
    return _from_objs;
}

const std::vector<Object *> &Relation::get_to_objs() const {
    return _to_objs;
}

bool Relation::add_from_obj(Object *pobj) {
    if (pobj->add_from_rlt(this)) {
        _from_objs.push_back(pobj);
    }
    return true;
}

bool Relation::add_to_obj(Object *pobj) {
    if (pobj->add_to_rlt(this)) {
        _to_objs.push_back(pobj);
    }
    return true;
}
/*
bool Relation::can_perform(const Object *pobj) const {
    return false;
}

std::vector<Object *> Relation::get_objs_need_value() const {
    return vector<Object *>();
}

bool Relation::perform(std::vector<Object *> &need_objs) {
    return false;
}
*/