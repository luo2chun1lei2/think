#pragma once

#include <string>
#include <vector>
#include <initializer_list>

#include <core/Value.hpp>

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
class Object : public IValue
{
public:

	Object(const std::string name);
	virtual ~Object() {}

	///////////////////////////////////////////////////////
	// Object-Relation Net

	virtual std::string get_name() const;

	virtual size_t get_count_of_rlts();
	virtual const std::vector<Relation *> & get_rlts() const;
	virtual Relation * get_rlt(uint32_t index);
	virtual bool contain_rlt(Relation * rlt) const;
	// Only add a relation to this object.
	virtual bool add_rlt(Relation * rlt);
	//	virtual void del_rlt(Relation * rlt);

	// get value of property.
	virtual Object * get_property(const std::string rlt_name, const std::string obj_name) const;

	virtual std::vector<Object *> get_property(const std::string rlt_name) const;

	///////////////////////////////////////////////////////
	// Perform

	/**
	 * 开始通知。
	 */
	virtual bool begin_notify();
    virtual bool notify(Object *obj);
    virtual bool end_notify();

	///////////////////////////////////////////////////////
	// 持有(Hold) ： IValue
	// TODO: 是否应该将 IValue的实现移动到 Object 类中？
	virtual Value get_value();
    virtual void set_value(Value value);

protected:

	std::string name;
	std::vector<Relation *> relations;

	// get_value & set_value
	Value value;

private:
};

/**
 * 关系，继承对象。
 */
class Relation: public Object
{
public:

	Relation(const std::string name);
	virtual ~Relation();

	///////////////////////////////////////////////////////
	// Object-Relation Net
	virtual bool relate(std::initializer_list<Object *> il);
	virtual size_t get_count_of_objs();
	virtual Object * get_obj(uint32_t index);
	virtual bool add_obj(Object * pobj);

	virtual const std::vector<Object *> & get_objects() const;

	///////////////////////////////////////////////////////
	// Perform
	/**
     * 运转这个关系。
     * @return true:成功运转，false:中间出现错误。
     */
    virtual bool perform();

protected:

	// Relation也是一个对象，所以也会有自己的属性，那么就不能复用 Object::relations。
	std::vector<Object *> objects;

private:

};
