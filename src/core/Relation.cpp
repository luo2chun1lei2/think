#include <core/Relation.hpp>

#include <initializer_list>

#include <misc/Misc.hpp>

using namespace std;

Relation::Relation(const std::string name)
    : Object(name) {
}

Relation::~Relation() {
}

bool Relation::relate(initializer_list<Object *> il) {

    for (auto beg = il.begin(); beg != il.end(); ++beg) {
        if (add_obj(*beg) == false) {
            LOGE("Cannot add object into relation.");
            return false;
        }
    }

    return true;
}

bool Relation::relate(std::vector<Object *> objs) {
    for (auto beg = objs.begin(); beg != objs.end(); ++beg) {
        if (add_obj(*beg) == false) {
            LOGE("Cannot add object into relation.");
            return false;
        }
    }

    return true;
}

size_t Relation::get_count_of_objs() {
    return objects.size();
}

Object *Relation::get_obj(uint32_t index) {
    return objects[index];
}

const std::vector<Object *> &Relation::get_objects() const {
    return objects;
}

bool Relation::add_obj(Object *pobj) {
    if (pobj->add_rlt(this)) {
        objects.push_back(pobj);
    }
    return true;
}

bool Relation::can_perform(const Object *pobj) const {
    return false;
}

std::vector<Object *> Relation::get_objs_need_value() const {
    return vector<Object *>();
}

bool Relation::perform(std::vector<Object *> &need_objs) {
    return false;
}
