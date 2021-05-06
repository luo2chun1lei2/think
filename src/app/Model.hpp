#pragma once

#include <vector>
#include <map>
#include <string>

#include <core/Object.hpp>
#include <core/Relation.hpp>

// 第一个string：关系的名字。
// 第二个string：关系涉及到的对象的名字。
typedef std::map<std::string, std::string> Properties;

/**
 * TODO: model 可以看做一个区域，等同于 {}，region/range ？
 * 内部包含一个OR-Net，可以通过通用的命令来管理。
 * 但是内部OR-Net分析时，不包含这个Model。
 * 因为不能将对象内部的对象的指针传递到外部，所以接口都用 object name 来标示对象。
 * TODO: 以后可以作为一个比较特殊的对象来实现。
 */
class Model
{
public:
	Model(const std::string name);
	Model(const Model &mdl) = delete;
	virtual ~Model();

    // 添加一个对象。
	virtual bool add_obj(std::string name, Properties properties);

	// 添加一个对象的属性。
	virtual bool add_prop_of_obj(std::string obj_name, std::string rlt_name, std::string to_name);
	#if 0
	// 删除一个对象。
	virtual bool remove_obj(std::string obj_name);
	// 根据名字找到对象，是否存在。
	virtual bool have_obj_by_name(const std::string name) const;
	// 根据对象名字和相关的关系名字找到涉及到的对象的名字。
	std::vector<std::string> find_obj_by_obj_rlt(const std::string obj_name, const std::string rlt_name) const;
	// 根据关系的名字，找到关系涉及的对象的名字。
	std::vector<std::string> find_obj_by_rlt(const std::string rlt_name) const;

	virtual bool add_rlt(std::string name, Properties properties);



	virtual size_t get_elm_count() const;

    // 查找一个对象。

	virtual Element * find_elm(const ElementId id) const;
	
	virtual int index_of(const ElementId id) const;	// -1 : not found
	
	// 属性/TAG的原型：found = elm_name.rlt_name
	virtual std::vector<Element *> find_elm_by_rlt(const std::string elm_name, const std::string rlt_name) const;

	// 属性的函数。
	virtual std::vector<Element *> get_property_of_elm(const std::string elm_name, const std::string rlt_name) const;
	virtual bool set_property_of_elm(const std::string elm_name, const std::string rlt_name, const Element *to);
	virtual bool set_property_of_elm(Element *from, const std::string rlt_name, const std::string value);

#endif
protected:
	virtual Object * find_obj_by_name(const std::string name) const;
	virtual bool add_obj(Object * obj);

	std::vector<Object *> _objs;

private:
};