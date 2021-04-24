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
 * 1. 有一个名字，作为ID识别，不过名字的作用范围是有区域的，限于连接的对象。
 * 2. 包含多个关系，这些关系都和此对象有联系。但是并不是说有此关系一定会修改这个对象的状态。
 * 3. 每个对象都可以读取和设置值，不过并不是所有的对象都可以设置值，或者获取值。
 * 4. 是 subject-observer 的接受方(observer)。 【空实现】
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

	///////////////////////////////////
	// Object-Relation Path
	// get object by relation name and object name.
	virtual Object * get_property(const std::string rlt_name, const std::string obj_name) const;
	// get objects by relation name.
	virtual std::vector<Object *> get_property(const std::string rlt_name) const;

	///////////////////////////////////////////////////////
	// Perform
	// 算法：如果可以获取，就返回true，如果无法获取，就返回false，以及需要的object。

	// 如果改变，就通知变化了。
	// TODO: Map 和 数学运算 的做法兼容吗？
	virtual bool begin_notify();
    virtual bool notify(Object *obj);
    virtual bool end_notify();

	///////////////////////////////////////////////////////
	// 持有(Hold) ： IValue
	// TODO: 是否应该将 IValue的实现移动到 ObjValue 类中？
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
 * 关系，继承于对象。
 * 1. 关联若干相关对象，有影响方（affect）和被影响方(affected)。只有具体 Relation 自己知道。
 * 2. 运转相关函数。
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
	// 算法：如果可以获取，就返回true，如果无法获取，就返回false，以及需要的object。
	// 关系有两种运转，一种是可以“运转”出一个对象，比如 "a=b"；
	//     还有一种运转自己本身，比如"+(a,b)"。

	/**
	 * 标识：是否可以获取pobj的值？
	 * @param pobj 需要关系评估的对象。nullptr:评估自身是否可以获取值。
	 * true:可以，false：不可以。
	 */
	virtual bool can_perform(const Object * pobj) const;

	/**
	 * 如果可以获取pobj的值，那么还需要哪些对象要值？
	 * 比如 a=b+c，如果要运转，c设置值了，但是b没有设置值，那么就返回b。
	 */
	virtual std::vector<Object *> get_objs_need_value() const;

	/**
     * 运转这个关系。
	 * @param need_objs 必须是空的。
     * @return true:成功运转，false:运转失败，如果need_objs是空，那么就是不支持，如果不为空，就是支持但缺少。
     */
    virtual bool perform(std::vector<Object *> &need_objs);

protected:

	// Relation也是一个对象，所以也会有自己的属性，那么就不能复用 Object::relations。
	std::vector<Object *> objects;

private:

};
