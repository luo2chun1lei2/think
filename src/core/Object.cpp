#include <core/Object.hpp>

using namespace std;

/////////////////////////////////////////////////////////////////////

Object::Object(const std::string name) {
    this->name = name;
}

std::string Object::get_name() const {
    return this->name;
}

size_t Object::get_count_of_from_rlts() {
    return _from_rlts.size();
}

size_t Object::get_count_of_to_rlts() {
    return _to_rlts.size();
}

Relation *Object::get_from_rlt(uint32_t index) {
    return _from_rlts[index];
}

Relation *Object::get_to_rlt(uint32_t index) {
    return _to_rlts[index];
}

const std::vector<Relation *> &Object::get_from_rlts() const {
    return _from_rlts;
}

const std::vector<Relation *> &Object::get_to_rlts() const {
    return _to_rlts;
}

bool Object::contain_from_rlt(Relation *rlt) const {
    for (auto r : _from_rlts) {
        if (r == rlt) {
            return true;
        }
    }

    return false;
}

bool Object::contain_to_rlt(Relation *rlt) const {
    for (auto r : _to_rlts) {
        if (r == rlt) {
            return true;
        }
    }

    return false;
}

bool Object::add_from_rlt(Relation *rlt) {
    if (rlt == nullptr) {
        return false;
    }

    if (contain_from_rlt(rlt)) {
        // Has contained it.
        return false;
    }

    _from_rlts.push_back(rlt);

    return true;
}

bool Object::add_to_rlt(Relation *rlt) {
    if (rlt == nullptr) {
        return false;
    }

    if (contain_to_rlt(rlt)) {
        // Has contained it.
        return false;
    }

    _to_rlts.push_back(rlt);

    return true;
}

void Object::add_property(const std::string rlt_name, const std::string obj_name, const Value value)
{
	Relation * rlt = new Relation(rlt_name);
	// 这里不知道“值对象”！
	Object * to = new Object(obj_name);

	// TODO: 这里有的问题，怎么设值？
	to->set_value(value);

	rlt->relate({this}, {to});
}

Object *Object::get_property(const std::string rlt_name, const std::string obj_name) const {
    for (auto r : this->_from_rlts) {
        if (r->get_name() == rlt_name) {
            for (auto o : r->get_to_objs()) {
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
    for (auto r : this->_from_rlts) {
        if (r->get_name() == rlt_name) {
            for (auto o : r->get_to_objs()) {
                if (o != this) {
                    results.push_back(o);
                }
            }
        }
    }

    return results;
}

void Object::set_property(const std::string rlt_name, const std::string obj_name, const Value value)
{
	Object * found_obj = get_property(rlt_name, obj_name);
	if (found_obj) {
		found_obj->set_value(value);
	} else {
		add_property(rlt_name, obj_name, value);
	}
}

bool Object::begin_notify() {
    return false;
}

bool Object::notify(Object *obj) {
    return false;
}

bool Object::end_notify() {
    return false;
}

Value Object::get_value() {
    return value;
}
void Object::set_value(Value value) {
    this->value = value;
}
