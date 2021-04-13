#include <Relation.hpp>

#include <stdarg.h>

#include <Misc.hpp>

using namespace std;

Relation::Relation(const std::string name)
    : Object(name) {
    // this->from = this->to = nullptr;
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

#if 0
Relation::Relation(const Relation &rlt)
    : Element(rlt) {
    this->from = this->to = nullptr;
}



void Relation::relate(Element *from, Element *to) {
    this->from = from;
    this->to = to;
}

// 得到此关系涉及到元素，按照序号。
// 如果不存在，就会返回NULL。
Element *Relation::get_from() const {
    return this->from;
}

Element *Relation::get_to() const {
    return this->to;
}

#endif