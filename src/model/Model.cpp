#include <Model.hpp>

using namespace std;

 Model::Model(const std::string name):Element(name)
{
}

Model::~Model()
{
	elms.clear();
}

bool Model::add_elm(Element * elm)
{
	if (elm == nullptr) {
		return false;
	}

	if (find_elm(elm->get_id()) != nullptr) {
		return false;
	}

	elms.push_back(elm);

	return true;
}

Element *Model::get_elm(uint32_t no) const
{
	if (no >= elms.size()) {
		return nullptr;
	} else {
		return elms[no];
	}
}

size_t Model::get_elm_count() const
{
	return elms.size();
}

Element *Model::find_elm(const ElementId id) const
{
 for (auto e:elms) {
		if (e->get_id() == id) {
			return e;
		}
	}

	return nullptr;
}

vector < Element * >Model::find_elm(const std::string name) const
{
	vector < Element * >found;
 	for (auto e:elms) {
		if (e->get_name() == name) {
			found.push_back(e);
		}
	}

	return found;
}

int Model::index_of(const ElementId id) const
{
	for(int i=0; i<elms.size(); i++) {
		if (elms[i]->get_id() == id) {
			return i;
		}
	}
	
	return -1;
}

// 语义是：elm的rlt关系对应的elm是什么。
// 但是elm允许有同名的关系，比如某个人的亲戚，可以有很多。
// find to = from.rlt.
std::vector <Element * >Model::find_elm_by_rlt(const std::string elm_name,
						const std::string rlt_name)
{
	vector <Element * >found;

	vector <Element * >found_rlts = find_elm(rlt_name);
	for (auto elm: found_rlts) {
		Relation * rlt = dynamic_cast<Relation *>(elm);
		Element * e = rlt->get_from();
		if (e->get_name() == elm_name) {
			found.push_back(rlt->get_to());
		}
	}

	return found;
}
