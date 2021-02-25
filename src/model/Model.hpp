#pragma once

#include <vector>
#include <string>

#include <Element.hpp>
#include <Relation.hpp>

/**
 * 包含若干元素，这些元素和外部的模型没有关系。
 * TODO: 以后必然会融合多个模型，以后模型就是组合元素。
 */
class Model : public Element
{
public:
	Model(const std::string name);
	Model(const Model &mdl) = delete;
	virtual ~Model();
	
	virtual bool add_elm(Element *elm);
	virtual size_t get_elm_count() const;
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
	
private:
};