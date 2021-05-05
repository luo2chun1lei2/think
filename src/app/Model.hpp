#pragma once

#include <vector>
#include <string>

#include <core/Object.hpp>
#include <core/Relation.hpp>

/**
 * 内部包含一个OR-Net，可以通过通用的命令来管理。
 * 但是内部OR-Net分析时，不包含这个Model。
 */
class Model
{
public:
	Model(const std::string name);
	Model(const Model &mdl) = delete;
	virtual ~Model();
#if 0
    // 添加一个对象
	virtual bool add_elm(Element *elm);
	virtual size_t get_elm_count() const;

    // 查找一个对象。
	virtual Element * get_elm(uint32_t no) const;
	virtual Element * find_elm(const ElementId id) const;
	std::vector<Element *> find_elm(const std::string name) const;
	virtual int index_of(const ElementId id) const;	// -1 : not found
	
	// 属性/TAG的原型：found = elm_name.rlt_name
	virtual std::vector<Element *> find_elm_by_rlt(const std::string elm_name, const std::string rlt_name) const;

	// 属性的函数。
	virtual std::vector<Element *> get_property_of_elm(const std::string elm_name, const std::string rlt_name) const;
	virtual bool set_property_of_elm(const std::string elm_name, const std::string rlt_name, const Element *to);
	virtual bool set_property_of_elm(Element *from, const std::string rlt_name, const std::string value);
	
protected:
	std::vector<Element *> elms;
#endif
private:
};