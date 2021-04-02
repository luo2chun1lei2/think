#include <Object.hpp>
//#include <ElementId.hpp>

/////////////////////////////////////////////////////////////////////

Object::Object(const std::string name) {
    //id = ElementIdFactory::get_instance()->generate();
    this->name = name;
    //this->value = "";
}

std::string Object::get_name() const {
    return this->name;
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