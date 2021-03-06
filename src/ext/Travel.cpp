#include <ext/Travel.hpp>

#include <algorithm>
#include <vector>

#include <misc/Misc.hpp>

using namespace std;

#ifdef TRACE

static void trace(int line, vector<Object *> objs)
{
    printf("trace: L%d\n", line);
    for( auto o : objs) {
        printf("  obj: %s\n", o->get_name().c_str());
    }
}

static void trace(int line, vector<Relation *> objs)
{
    printf("trace: L%d\n", line);
    for( auto o : objs) {
        printf("  rlt: %s\n", o->get_name().c_str());
    }
}
#else
static void trace(int line, vector<Object *> objs) {}
static void trace(int line, vector<Relation *> objs) {}
#endif

bool Travel::travel(Object *pobj, TravelMode travel_mode) {
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
        Relation *rlt = dynamic_cast<Relation *>(wait);
        if (rlt) { // 如果是关系的话，

            if (write_log)
                LOGI("Rlt:%s\n", rlt->get_name().c_str());

            if (on_meet_rlt(rlt) == false) {
                break;
            }

            // 需要处理关系涉及到的对象
            if (travel_mode == TRAVEL_BY_ALL || travel_mode == TRAVEL_BY_TO) {
                trace(__LINE__, rlt->get_from_objs());
                waits.insert(waits.end(), rlt->get_from_objs().begin(), rlt->get_from_objs().end());
            }
            if (travel_mode == TRAVEL_BY_ALL || travel_mode == TRAVEL_BY_FROM) {
                trace(__LINE__, rlt->get_to_objs());
                waits.insert(waits.end(), rlt->get_to_objs().begin(), rlt->get_to_objs().end());
            }

            // 关系本身也是一个对象，所以需要加入和它相关的关系。
            if (travel_mode == TRAVEL_BY_ALL || travel_mode == TRAVEL_BY_FROM) {
                trace(__LINE__, rlt->get_from_rlts());
                waits.insert(waits.end(), rlt->get_from_rlts().begin(), rlt->get_from_rlts().end());
            }
            if (travel_mode == TRAVEL_BY_ALL || travel_mode == TRAVEL_BY_TO) {
                trace(__LINE__, rlt->get_to_rlts());
                waits.insert(waits.end(), rlt->get_to_rlts().begin(), rlt->get_to_rlts().end());
            }

        } else { // 如果是对象的话，
            if (write_log)
                LOGI("Obj:%s\n", wait->get_name().c_str());

            if (on_meet_obj(wait) == false) {
                break;
            }

            // 对象
            if (travel_mode == TRAVEL_BY_ALL || travel_mode == TRAVEL_BY_FROM) {
                trace(__LINE__, wait->get_from_rlts());
                waits.insert(waits.end(), wait->get_from_rlts().begin(), wait->get_from_rlts().end());
            }
            if (travel_mode == TRAVEL_BY_ALL || travel_mode == TRAVEL_BY_TO) {
                trace(__LINE__, wait->get_to_rlts());
                waits.insert(waits.end(), wait->get_to_rlts().begin(), wait->get_to_rlts().end());
            }
        }

        // record than it has been processed.
        dones.push_back(wait);

    } while (true);

    return true;
}