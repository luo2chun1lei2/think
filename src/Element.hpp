#pragma once

#include <ElementId.hpp>

/**
 * 所有的元素的基类。
 */
class Element
{
public:
	Element();
	Element(const Element &elm);
	virtual ~Element() {}
	
	virtual ElementId get_id();
	
protected:
	ElementId id;
private:
};

class BasicElement : public Element
{
public:
protected:
private:
};
