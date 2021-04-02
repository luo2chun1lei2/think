#pragma once

#if 0
#include <vector>
#include <string>
#include <initializer_list>
#endif

#include <Element.hpp>

/**
 * 有方向的关系，这个普遍的关系形式，就不在名字上区分了。
 */
class Relation: public Object
{
public:
/*
	Relation(const std::string name);
	Relation(const Relation &rlt);
	virtual ~Relation();
	
	// 设置关系，这个是有方向的。
	// 每次设置，都会清理之前的设定，然后重新设置。
	virtual void relate(Element *from, Element *to);
	// 得到此关系涉及到元素，按照序号。
	// 如果不存在，就会返回NULL。
	virtual Element * get_from() const;
	virtual Element * get_to() const;
	
protected:
	// 关联的元素列表。
	Element *from;
	Element *to;
private:
*/
};