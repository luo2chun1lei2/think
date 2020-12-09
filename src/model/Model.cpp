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

// TODO: 目前的问题是relation中没有方向。
std::vector < Element * >Model::find_elm_by_rlt(const std::string elm_name,
						const std::string rlt_name)
{
	vector < Element * >found;

	vector < Element * >found_rlts = find_elm(rlt_name);
 for (auto rlt:found_rlts) {

		vector < Element * >elms =
		    dynamic_cast < Relation * >(rlt)->get_elms();
		bool got = false;
 for (auto e:	elms) {
			if (e->get_name() == elm_name) {
				got = true;
			}
		}

		if (got) {
 for (auto e:		elms) {
				if (e->get_name() != elm_name) {
					found.push_back(e);
				}
			}
		}
	}

	return found;
}
