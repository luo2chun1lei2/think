#include <ext/Travel.hpp>

#include <algorithm>
#include <vector>

#include <misc/Misc.hpp>

using namespace std;

bool Travel::travel(Object *pobj) {
    // 记录已经遍历后的对象。
    vector<Object *> dones;

    // 记录还没有遍历的对象。
    vector<Object *> waits;

    waits.push_back(pobj);

    do {
        // no more waiting objects, so break.
        if (waits.empty()) {
            break;
        }
        Object *wait = waits.back();
        waits.pop_back();

        // LOGE("pop %s\n", typeid(*wait).name());

        // If proces it ago, then ignore it.
        if (std::find(dones.begin(), dones.end(), wait) != dones.end()) {
            continue;
        }

        // process it.
        if (typeid(*wait) == typeid(Relation)) {
            Relation *rlt = (Relation *)wait;
            if (on_meet_rlt(rlt) == false) {
                break;
            }

            // for( auto o : rlt->get_objects()) {
            //     LOGE("insert o: %s\n", o->get_name().c_str());
            // }
            waits.insert(waits.end(), rlt->get_objects().begin(), rlt->get_objects().end());

            // for( auto o : rlt->get_rlts()) {
            //     LOGE("insert r: %s\n", o->get_name().c_str());
            // }
            // Relation is also a object, so it has relations.
            waits.insert(waits.end(), rlt->get_rlts().begin(), rlt->get_rlts().end());

        } else {
            if (on_meet_obj(wait) == false) {
                break;
            }

            // for( auto o : wait->get_rlts()) {
            //     LOGE("insert r: %s\n", o->get_name().c_str());
            // }
            waits.insert(waits.end(), wait->get_rlts().begin(), wait->get_rlts().end());
        }

        // record than it has been processed.
        dones.push_back(wait);

    } while (true);

    return true;
}