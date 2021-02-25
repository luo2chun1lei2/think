#pragma once

#include <string>

#include <ElementId.hpp>

/**
 * 所有的元素的基类。
 * 每个元素都必须
 * 1. 有一个唯一的ID，如果ID相同，就应该是一个元素，即使其他的属性都不同（这个应该是程序出现错误）。
 * 2. 以及一个名字。名字不需要唯一，后面元素可以自己判断是否需要唯一或者什么合法。
 */
class Element
{
public:
	Element(const std::string name);
	Element(const std::string name, const std::string value);
	Element(const Element &elm);
	virtual ~Element() {}
	
	virtual ElementId get_id() const;
	virtual std::string get_name() const;
	// 返回一个值，针对的是“值”类型的元素，比如数字、文字、布尔型等。
	// TODO: 是否应该建立一个 ElementValue 类型？
	virtual void set_value(const std::string value) {this->value = value;}
	virtual std::string get_value() const {return value;}
	
	virtual bool operator==(const Element &elm);
	virtual bool operator!=(const Element &elm);
	
protected:
	ElementId id;
	std::string name;

	std::string value;
private:
};
