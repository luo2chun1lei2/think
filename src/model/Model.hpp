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
	virtual Element * get_elm(uint32_t no) const;
	virtual Element * find_elm(const ElementId id) const;
	std::vector<Element *> find_elm(const std::string name) const;
	
	virtual std::vector<Element *> find_elm_by_rlt(const std::string elm_name, const std::string rlt_name);
	
protected:
	std::vector<Element *> elms;
	
private:
};