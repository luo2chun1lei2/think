#pragma once

#include <string>

//#include <ElementId.hpp>

/**
 * 因为下面的Object要用到Relation的指针，所以这里必须预先声明。
 */
class Relation;

/**
 * 所有对象的基类。
 * 对象有两个子类：元素和关系。
 * 包含功能：
 * 1. 有一个名字，作为ID识别，不过名字是有区域的，需要从root节点一路查找下去才行。
 * 2. 包含多个属性，属性必须是一个关系。
 */
class Object
{
public:

	Object(const std::string name);
	virtual ~Object() {}

	virtual std::string get_name() const;

	virtual size_t get_count_of_rlts();
	virtual Relation * get_rlt(uint32_t index);

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


/**
 * 关系，继承对象。
 */
class Relation: public Object
{
public:

	Relation(const std::string name);
/*
	Relation(const Relation &rlt);
	virtual ~Relation();
	
	// 设置关系，这个是有方向的。
	// 每次设置，都会清理之前的设定，然后重新设置。
	virtual void relate(Element *from, Element *to);
	// 得到此关系涉及到元素，按照序号。
	// 如果不存在，就会返回NULL。
	virtual Element * get_from() const;
	virtual Element * get_to() const;
*/
	virtual bool set_relation(...);
	virtual size_t get_count_of_objs();
	virtual Object * get_obj(uint32_t index);
protected:
	// 关联的元素列表。
//	Element *from;
//	Element *to;
private:

};
