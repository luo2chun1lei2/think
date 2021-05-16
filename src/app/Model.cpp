#include <app/Model.hpp>

#include <misc/Misc.hpp>

using namespace std;

Model::Model(const std::string name) {
}

Model::~Model() {
    _objs.clear();
}

std::vector<Object *> Model::get_objs() {
    return _objs;
}

bool Model::add_obj(std::string name, Properties properties) {
    // bool add_elm(Element *elm) {
    // Object *found = find_obj_by_name(name);
    // if (found) {
    //     return false;
    // }

    Object *found = new Object(name);
    add_obj(found);

    // TODO: properties 没有管！

    return true;
}

bool Model::add_rlt(std::string name, Properties properties) {
    // Object *found = find_obj_by_name(name);
    // if (!found) {
    //     return false;
    // }

    Relation *one = new Relation(name);
    add_rlt(one);

    // TODO: properties 没有管！

    return true;
}

bool Model::add_obj(Object *obj) {
    if (obj == nullptr) {
        return false;
    }
    _objs.push_back(obj);
    return true;
}

bool Model::add_rlt(Relation *rlt) {
    // TODO: 目前看relation和object的存储没有必要区分开成两个数组。
    return add_obj(rlt);
}

Object *Model::find_obj_by_name(const std::string name) const {
    vector<Object *> found;
    for (auto o : _objs) {
        if (o->get_name() == name) {
            found.push_back(o);
        }
    }

    // TODO: 多个对象的问题！
    if (found.empty()) {
        return nullptr;
    } else {
        return found[0];
    }
}

bool Model::add_prop_of_obj(std::string obj_name, std::string rlt_name, std::string to_name) {

    Object *found = find_obj_by_name(obj_name);
    if (!found) {
        return false;
    }

    // 创建 value, name=""就当做是匿名的！
    Object *obj = new Object(to_name);
    add_obj(obj);

    // 创建Relation
    Relation *rlt = new Relation(rlt_name);
    rlt->relate({obj, found});
    add_obj(rlt);

    return true;
}

bool Model::have_obj_by_name(const std::string name) const {
    for (auto e : _objs) {
        if (e->get_name() == name) {
            return true;
        }
    }

    return false;
}

bool Model::relate(const std::string rlt_name, std::vector<std::string> obj_names) {
    Relation *rlt = dynamic_cast<Relation *>(find_obj_by_name(rlt_name));
    if (rlt == nullptr) {
        LOGE("Related object(%s) doesn't exist.\n", rlt_name.c_str());
        return false;
    }

    vector<Object *> objs_list;

    for (auto obj_name = obj_names.begin(); obj_name != obj_names.end(); ++obj_name) {
        Object *obj = find_obj_by_name(*obj_name);
        if (obj == nullptr) {
            LOGE("Related object(%s) doesn't exist.\n", (*obj_name).c_str());
            return false;
        }
        objs_list.push_back(obj);
    }
    rlt->relate(objs_list);

    return true;
}

// Element *Model::get_elm(uint32_t no) const {
//     if (no >= elms.size()) {
//         return nullptr;
//     } else {
//         return elms[no];
//     }
// }

// size_t Model::get_elm_count() const {
//     return elms.size();
// }

// Element *Model::find_elm(const ElementId id) const {
//     for (auto e : elms) {
//         if (e->get_id() == id) {
//             return e;
//         }
//     }

//     return nullptr;
// }

// vector<Element *> Model::find_elm(const std::string name) const {

// }

// int Model::index_of(const ElementId id) const {
//     for (int i = 0; i < elms.size(); i++) {
//         if (elms[i]->get_id() == id) {
//             return i;
//         }
//     }

//     return -1;
// }

// // 语义是：elm的rlt关系对应的elm是什么。
// // 但是elm允许有同名的关系，比如某个人的亲戚，可以有很多。
// // find to = from.rlt.
// std::vector<Element *> Model::find_elm_by_rlt(const std::string elm_name, const std::string rlt_name) const {
//     vector<Element *> found;

//     vector<Element *> found_rlts = find_elm(rlt_name);
//     for (auto elm : found_rlts) {
//         Relation *rlt = dynamic_cast<Relation *>(elm);
//         Element *e = rlt->get_from();
//         if (e->get_name() == elm_name) {
//             found.push_back(rlt->get_to());
//         }
//     }

//     return found;
// }

// std::vector<Element *> Model::get_property_of_elm(const std::string elm_name, const std::string rlt_name) const {
//     return find_elm_by_rlt(elm_name, rlt_name);
// }

// bool Model::set_property_of_elm(const std::string elm_name, const std::string rlt_name, const Element *to) {
//     // NO IMPL
//     return false;
// }
