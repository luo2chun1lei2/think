#include <Relation.hpp>

Relation::Relation(const std::string name):Element(name)
{
}

Relation::Relation(const Relation & rlt):Element(rlt)
{
}

Relation::~Relation()
{
	this->elms.clear();
}

// 设置多个对象到此关系中，添加先后的顺序有重要关系。
// 每次设置，都会清理之前的设定，然后重新设置。
void Relation::relate(std::initializer_list < Element * >lst)
{
	this->elms.clear();	// 不负责释放。
	for (auto e:lst) {
		this->elms.push_back(e);
	}
}

// 得到此关系涉及到元素，按照序号。
// 如果不存在，就会返回NULL。
const Element *Relation::get_elm(uint32_t no) const
{
	if (no >= elms.size()) {
		return nullptr;
	} else {
		return this->elms[no];
	}
}

size_t Relation::get_elm_count() const
{
	return this->elms.size();
}

std::vector < Element * >Relation::get_elms() const
{
	return this->elms;
}
