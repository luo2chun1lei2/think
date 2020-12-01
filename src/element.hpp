#pragma once

#include <uuid/uuid.h>

/**
 * id 的类型，这里想用uuid来设定，保证大部分不会重复。
 * 这样之后元素和model融合就不会冲突。
 */
typedef uuid_t elm_id_t;

class ElementId
{
public:
	ElementId();
	ElementId(const ElementId &id);
	virtual ~ElementId();
	
	virtual bool is_empty();
	virtual void clear();
	virtual bool generate();
	
	virtual bool operator==(const ElementId &elm_id);
	virtual bool operator!=(const ElementId &elm_id);
	
protected:
	elm_id_t id;
	
private:
};

/**
 * 所有的元素的基类。
 */
class Element
{
public:
	
protected:
	elm_id_t id;
private:
};