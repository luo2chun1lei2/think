#include <Element.hpp>
#include <ElementId.hpp>

/////////////////////////////////////////////////////////////////////

Element::Element()
{
	id = ElementIdFactory::get_instance()->generate();
}

Element::Element(const Element &elm)
{
	id = elm.id;
}

ElementId Element::get_id() const
{
	return this->id;
}

bool Element::operator==(const Element &elm)
{
	return elm.get_id() == this->get_id();
}

bool Element::operator!=(const Element &elm)
{
	return ! (*this == elm);
}
