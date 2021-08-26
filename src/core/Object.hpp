#pragma once

#include <initializer_list>
#include <string>
#include <vector>

#include <core/DynamicInterface.hpp>

/**
 * 因为下面的Object要用到Relation的指针，所以这里必须预先声明。
 */
class Relation;

/**
 * 所有对象的基类，本身就是一个简单的对象，所有的属性都是通过property来设定的。
 * 内部动态的接口。
 * 包含功能：
 * * ID
 *   1. 有一个ID，可以作为名字，不保证唯一性。
 *   2. ID的作用范围是有区域的，限于连接的对象。
 * * 关系
 *   1. 包含多个关系，这些关系都和此对象有联系。但是并不是说有此关系一定会修改这个对象的状态。
 * * 内部动态接口：
 *   可以动态指定一个对象实现了某些接口，不是给外部用的。
 */
class Object : public DynamicInterface {
public:
    Object(const std::string id);
    virtual ~Object() {
    }

    ///////////////////////////////////////////////////////
    // Object-Relation Net

    // 每个对象都有一个名字，但是并不是全局唯一，需要由容器来决定。
    virtual std::string get_id() const;
    virtual void set_id(std::string id);

    // 对象的from关系数目。
    virtual size_t get_count_of_from_rlts();
    virtual const std::vector<Relation *> &get_from_rlts() const;
    virtual Relation *get_from_rlt(uint32_t index);
    virtual bool contain_from_rlt(Relation *rlt) const;
    // Add a "from" relation of this object.
    virtual bool add_from_rlt(Relation *rlt);

    // 对象的 to 关系数目。
	virtual size_t get_count_of_to_rlts();
	virtual const std::vector<Relation *> &get_to_rlts() const;
	virtual Relation *get_to_rlt(uint32_t index);
	virtual bool contain_to_rlt(Relation *rlt) const;
    // Add a "to" relation of this object.
	virtual bool add_to_rlt(Relation *rlt);
    
    // TODO: 删除还没有实现。
    //	virtual void del_rlt(Relation * rlt);

    ///////////////////////////////////
    // 属性: 也是关系，但是可以实现快捷的操作。
    // obj1 -- rlt --> obj2 = obj1.rlt = obj2
    // Object-Relation Path

    // 在此对象上，添加一个属性。
//	virtual void add_property(const std::string rlt_id, const std::string obj_id, const Object *obj);

    // 在此对象上，设定一个属性的值，如果属性并不存在，就添加。
    //virtual void set_property(const std::string rlt_id, const std::string obj_name, const Object *obj);

    // get object by relation name and object name.
    virtual Object *get_property(const std::string rlt_id, const std::string obj_id) const;
    // get objects by relation name.
    virtual std::vector<Object *> get_property(const std::string rlt_id) const;

    ///////////////////////////////////////////////////////
    // Perform
    // 算法：如果可以获取，就返回true，如果无法获取，就返回false，以及需要的object。

    // 如果改变，就通知变化了。
    // TODO: Map 和 数学运算 的做法兼容吗？
/*
    virtual bool begin_notify();
    virtual bool notify(Object *obj);
    virtual bool end_notify();
*/
    ///////////////////////////////////////////////////////
    // 持有(Hold) ： IValue
    // 数值的部分，作为整个Object的共通逻辑，而不是只有值对象。
    // 后面如果开发出了类型，那么这里可以再思考。
//    virtual Value get_value();
//    virtual void set_value(Value value);

protected:
    std::string _id;

	// 从此对象开始的关系，就是rlt.from 有此对象。
    std::vector<Relation *> _from_rlts;
	// 到此对象开始的关系，就是rlt.to 有此对象。
	std::vector<Relation *> _to_rlts;

    // get_value & set_value
//    Value value;

private:
};

/**
 * 关系，继承于对象。
 * 1. 关联若干相关对象，有影响方（from）和被影响方(to)。只有具体 Relation 自己知道。
 * 2. 运转相关函数。
 */
class Relation : public Object {
public:
    Relation(const std::string name);
    virtual ~Relation();

    ///////////////////////////////////////////////////////
    // Object-Relation Net
    virtual bool relate(std::initializer_list<Object *> from_objs, std::initializer_list<Object *> to_objs);
    virtual bool relate(std::vector<Object *> from_objs, std::vector<Object *> to_objs);

    virtual size_t get_count_of_from_objs();
    virtual size_t get_count_of_to_objs();

    virtual Object *get_from_obj(uint32_t index);
    virtual Object *get_to_obj(uint32_t index);

    virtual bool add_from_obj(Object *pobj);
    virtual bool add_to_obj(Object *pobj);

    virtual const std::vector<Object *> &get_from_objs() const;
    virtual const std::vector<Object *> &get_to_objs() const;

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
//    virtual bool can_perform(const Object *pobj) const;

    /**
     * 如果可以获取pobj的值，那么还需要哪些对象要值？
     * 比如 a=b+c，如果要运转，c设置值了，但是b没有设置值，那么就返回b。
     */
//    virtual std::vector<Object *> get_objs_need_value() const;

    /**
     * 运转这个关系。
     * @param need_objs 必须是空的。
     * @return true:成功运转，false:运转失败，如果need_objs是空，那么就是不支持，如果不为空，就是支持但缺少。
     */
//    virtual bool perform(std::vector<Object *> &need_objs);

protected:
    // Relation也是一个对象，所以也会有自己的属性，那么就不能复用 Object::relations。
    std::vector<Object *> _from_objs;
    std::vector<Object *> _to_objs;

private:
};
