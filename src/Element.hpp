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
	
	virtual ElementId get_id() const;
	
	virtual bool operator==(const Element &elm);
	virtual bool operator!=(const Element &elm);
	
protected:
	ElementId id;
private:
};
