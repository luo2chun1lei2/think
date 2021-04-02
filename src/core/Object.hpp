#pragma once

#include <string>

//#include <ElementId.hpp>

/**
 * 所有对象的基类。
 * 对象有两个子类：元素和关系。
 */
class Object
{
public:

	Object(const std::string name);
	virtual ~Object() {}

	virtual std::string get_name() const;
#if 0
	Object(const std::string name, const std::string value);
	Object(const Object &elm);
	
	virtual ElementId get_id() const;
	
	// 返回一个值，针对的是“值”类型的元素，比如数字、文字、布尔型等。
	// TODO: 是否应该建立一个 ElementValue 类型？
	virtual void set_value(const std::string value) {this->value = value;}
	virtual std::string get_value() const {return value;}
	
	virtual bool operator==(const Element &elm);
	virtual bool operator!=(const Element &elm);
#endif
protected:

	std::string name;
#if 0
	ElementId id;
	

	std::string value;
#endif
private:
};