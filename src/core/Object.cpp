#include <Object.hpp>
//#include <ElementId.hpp>

/////////////////////////////////////////////////////////////////////

Object::Object(const std::string name) {
    // id = ElementIdFactory::get_instance()->generate();
    this->name = name;
    // this->value = "";
}

std::string Object::get_name() const {
    return this->name;
}

size_t Object::get_count_of_rlts() {
    return relations.size();
}

Relation *Object::get_rlt(uint32_t index) {
    return relations[index];
}

bool Object::contain_rlt(Relation *rlt) const {
    for (auto r : relations) {
        if (r == rlt) {
            return true;
        }
    }

    return false;
}

bool Object::add_rlt(Relation *rlt) {
    if (rlt == nullptr) {
        return false;
    }

    if (contain_rlt(rlt)) {
        // Has contained it.
        return false;
    }

    relations.push_back(rlt);

    return true;
}

#if 0
Element::Element(const std::string name, const std::string value) {
    id = ElementIdFactory::get_instance()->generate();
    this->name = name;
    this->value = value;
}

Element::Element(const Element &elm) {
    id = elm.id;
    name = elm.name;
    value = elm.value;
}

ElementId Element::get_id() const {
    return this->id;
}



bool Element::operator==(const Element &elm) {
    return elm.get_id() == this->get_id();
}

bool Element::operator!=(const Element &elm) {
    return !(*this == elm);
}
#endif