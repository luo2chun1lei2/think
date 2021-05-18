#include <fwk/RltShow.hpp>

#include <vector>

#include <ext/Travel.hpp>
#include <misc/Misc.hpp>

using namespace std;

RltShow::RltShow(const std::string name)
    : Relation(name) {
}

RltShow::~RltShow() {
}

class MyTravel : public Travel {
public:
    vector<Object *> objs;
    vector<Relation *> rlts;

protected:
    virtual bool on_meet_obj(Object *pobj) {
        objs.push_back(pobj);
        return true;
    }

    virtual bool on_meet_rlt(Relation *prlt) {
        rlts.push_back(prlt);
        return true;
    }

private:
};

// TODO: 是传递整个OR-Net，还是一个一个传递？
bool RltShow::perform() {
    if (this->_from_objs.size() < 1 || this->_to_objs.size() < 1) {
        LOGE("Show needs two objects.\n");
        return false;
    }

    MyTravel travel;

    Object *to = this->_to_objs[0];
    Object *from = this->_from_objs[0];

    travel.travel(from);

    if (!to->begin_notify()) {
        return false;
    }

    // 通用的接口，应该不用搞这么复杂！
    for (Object *obj : travel.objs) {
        // 自己本身不算在内。
        // TODO: 这个算法位置不对，应该放在Travel中实现。
        if (obj == this) {
            continue;
        }

        if (!to->notify(obj)) {
            return false;
        }
    }

    for (Relation *rlt : travel.rlts) {
        if (!to->notify(rlt)) {
            return false;
        }
    }

    if (!to->end_notify()) {
        return false;
    }

    return true;
}
