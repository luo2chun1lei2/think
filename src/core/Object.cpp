#include <Object.hpp>

using namespace std;

/////////////////////////////////////////////////////////////////////

Object::Object(const std::string name) {
    this->name = name;
}

std::string Object::get_name() const {
    return this->name;
}

size_t Object::get_count_of_rlts() {
    return relations.size();
}

Relation *Object::get_rlt(uint32_t index) {
    return relations[index];
}

const std::vector<Relation *> & Object::get_rlts() const
{
    return relations;
}

bool Object::contain_rlt(Relation *rlt) const {
    for (auto r : relations) {
        if (r == rlt) {
            return true;
        }
    }

    return false;
}

bool Object::add_rlt(Relation *rlt) {
    if (rlt == nullptr) {
        return false;
    }

    if (contain_rlt(rlt)) {
        // Has contained it.
        return false;
    }

    relations.push_back(rlt);

    return true;
}

Object *Object::get_property(const std::string rlt_name, const std::string obj_name) const {
    for (auto r : this->relations) {
        if (r->get_name() == rlt_name) {
            for (auto o : r->get_objects()) {
                if (o != this && o->get_name() == obj_name) {
                    return o;
                }
            }
        }
    }

    return nullptr;
}

std::vector<Object *> Object::get_property(const std::string rlt_name) const {
    vector<Object *> results;
    for (auto r : this->relations) {
        if (r->get_name() == rlt_name) {
            for (auto o : r->get_objects()) {
                if (o != this) {
                    results.push_back(o);
                }
            }
        }
    }

    return results;
}
