#include <Element.hpp>
#include <ElementId.hpp>

/////////////////////////////////////////////////////////////////////

Element::Element(const std::string name)
{
	id = ElementIdFactory::get_instance()->generate();
	this->name = name;
}

Element::Element(const Element &elm)
{
	id = elm.id;
	name = elm.name;
}

ElementId Element::get_id() const
{
	return this->id;
}

std::string Element::get_name() const
{
	return this->name;
}

bool Element::operator==(const Element &elm)
{
	return elm.get_id() == this->get_id();
}

bool Element::operator!=(const Element &elm)
{
	return ! (*this == elm);
}
