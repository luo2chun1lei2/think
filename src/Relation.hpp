#pragma once

#include <vector>
#include <initializer_list>

#include <Element.hpp>

class Relation: public Element
{
public:
	Relation();
	Relation(const Relation &rlt);
	virtual ~Relation();
	
	// 设置多个对象到此关系中，添加先后的顺序有重要关系。
	// 每次设置，都会清理之前的设定，然后重新设置。
	virtual void relate(std::initializer_list<Element*> lst);
	// 得到此关系涉及到元素，按照序号。
	// 如果不存在，就会返回NULL。
	virtual const Element * get_elm(uint32_t no);
	
protected:
	// 关联的元素列表。
	std::vector<Element*> elms;
private:
};