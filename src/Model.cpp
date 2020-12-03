#include <Model.hpp>


Model::Model()
{
}

Model::~Model()
{
	elms.clear();
}

bool Model::add_elm(Element *elm)
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

Element * Model::get_elm(uint32_t no) const
{
	if (no >= elms.size()) {
		return nullptr;
	} else {
		return elms[no];
	}
}

Element * Model::find_elm(const ElementId id) const
{
	for(auto e : elms) {
		if(e->get_id() == id) {
			return e;
		}
	}
	
	return nullptr;
}
