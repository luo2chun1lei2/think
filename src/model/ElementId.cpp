#include <ElementId.hpp>

ElementId::ElementId()
{
	this->clear();
}

ElementId::ElementId(const ElementId & from)
{
	uuid_copy(this->id, from.id);
}

ElementId::~ElementId()
{
}

bool ElementId::operator==(const ElementId & elm_id)
{
	return uuid_compare(this->id, elm_id.id) == 0;
}

bool ElementId::operator!=(const ElementId & elm_id)
{
	return !(*this == elm_id);
}

void ElementId::clear()
{
	uuid_clear(id);
}

bool ElementId::generate()
{
	uuid_generate(id);
	return true;
}

bool ElementId::is_empty()
{
	return uuid_is_null(id);
}

///////////////////////////////////////////////////////////

ElementIdFactory *ElementIdFactory::factory = nullptr;

ElementId ElementIdFactory::generate()
{
	ElementId id;
	id.generate();
	return id;
}
