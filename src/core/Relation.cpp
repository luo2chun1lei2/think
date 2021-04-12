#include <Relation.hpp>

Relation::Relation(const std::string name)
    : Object(name) {
    // this->from = this->to = nullptr;
}

bool Relation::set_relation(...) {
    return false;
}

size_t Relation::get_count_of_objs() {
    return 0;
}

Object *Relation::get_obj(uint32_t index) {
    return nullptr;
}

#if 0
Relation::Relation(const Relation &rlt)
    : Element(rlt) {
    this->from = this->to = nullptr;
}

Relation::~Relation() {
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