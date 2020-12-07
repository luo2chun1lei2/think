#pragma once

#include <uuid/uuid.h>

typedef long int64_t;
typedef unsigned long uint64_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef unsigned short uint16_t;

typedef unsigned char uint8_t;

/**
 * Element ID 的类型，这里想用uuid来设定，保证大部分不会重复。
 * 这样之后元素和model融合就不会冲突。
 * 另外考虑到后面ElmentID会成为一个重要的功能，所以这里就建立了一个类型，以及一个工厂类。
 */

/**
 * Element Id的内部实际类型。
 */
typedef uuid_t elm_id_t;

/**
 * ElementID，重点是要保持唯一性。
 * 内置比较操作。
 */
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
 * 工厂类。单例模式。
 * 尽量保证模型输出是唯一的。
 */
class ElementIdFactory
{
public:
	static ElementIdFactory* get_instance() {
		if(factory == nullptr) {
			factory = new ElementIdFactory();
		}
		return factory;
	}
	// 产生唯一的 ID。
	ElementId generate();
protected:
	ElementIdFactory() {}	// 单例模式。
	virtual ~ElementIdFactory() {}
	
	static ElementIdFactory *factory;
private:
};

