#include <ext/Perform.hpp>

#include <algorithm>

#include <ext/Travel.hpp>
#include <misc/Misc.hpp>

using namespace std;

///////////////////////////////////////////////////////////

class MyTravel : public Travel {
public:
    MyTravel();

    bool is_end();

    virtual bool travel(Object *pobj);

protected:
    virtual bool on_meet_obj(Object *pobj);

    virtual bool on_meet_rlt(Relation *prlt);

    vector<Object *> last_oks;
    vector<Object *> cur_oks;

    Object *target;
    bool end;

private:
};

MyTravel::MyTravel() {
    end = false;
}

bool MyTravel::is_end() {
    return end;
}

bool MyTravel::travel(Object *pobj) {
    target = pobj;
    bool rtn = Travel::travel(pobj);

    // 无法再运转更多的对象，所以必须退出。
    if (cur_oks.size() == last_oks.size()) {
        end = true;
    } else {
        LOGE("%d=%d\n", cur_oks.size(), last_oks.size());
        last_oks.clear();
        LOGE("1 %d=%d\n", cur_oks.size(), last_oks.size());
        last_oks.insert(last_oks.end(), cur_oks.begin(), cur_oks.end());
        LOGE("2 %d=%d\n", cur_oks.size(), last_oks.size());
        cur_oks.clear();
        LOGE("3 %d=%d\n", cur_oks.size(), last_oks.size());
    }

    return rtn;
}

bool MyTravel::on_meet_obj(Object *pobj) {
    return true;
}

bool MyTravel::on_meet_rlt(Relation *prlt) {
    vector<Object *> needs;
    if (prlt->perform(needs)) {
        cur_oks.push_back(prlt);
    }

    if (target->get_value().get_type() != Value::TYPE_NONE) {
        end = true;
        return false;
    }

    return true;
}

PerformRound::PerformRound(int max_round) {
    this->max_round = max_round;
}
PerformRound::~PerformRound() {
}

bool PerformRound::perform(Object *pobj) {

    MyTravel my_travel;
    do {
        my_travel.travel(pobj);
    } while (!my_travel.is_end() && (max_round == -1 || --max_round > 0));

    if (pobj->get_value().get_type() == Value::TYPE_NONE) {
        return false;
    } else {
        return true;
    }
}

///////////////////////////////////////////////////////////

Perform::Perform() {
}

Perform::~Perform() {
}

bool Perform::on_meet_obj(Object *pobj) {
    return true;
}

bool Perform::on_meet_rlt(Relation *prlt) {
    return true;
}

/**
 * 原理：对象看自己是否有值，然后看相关关系是否可以运转自己的值。
 *      关系看自己是否可以运转自己的值，然后看相关关系是否可以运转自己的值。
 *      要点：关系自己不能设置值，只能根据属性获取值。而对象（非关系），可以设置值！
 * 算法：
 * 1. 找到制定对象是否有值？
 *   1. 有：返回值。
 *   2. 没有：跳转到2。
 * 2. 遍历制定对象的关联关系。问每个“关系”是否可以获取到关系值？
 *   1. 如果不行，继续其他关联关系。
 *   2. 如果可以，是否有欠缺“对象”没有值 ？
 *     1. 无：可以，就运行。
 *     2. 有：不可以，跳转到1，指定对象是“欠缺”的对象。
 */
bool Perform::perform(Object *pobj) {
    // 记录已经遍历后的对象。
    vector<Object *> dones;

    // 记录还没有遍历的对象。
    vector<Object *> waits;

    waits.push_back(pobj);

    do {
        // 没有需要修剪的对象，就可以退出。
        if (waits.empty()) {
            break;
        }

        // 得到需要处理的对象。
        Object *wait = waits.back();
        waits.pop_back();

        // LOGE("pop %s\n", typeid(*wait).name());

        // 如果之前已经处理过了，就忽略。
        if (std::find(dones.begin(), dones.end(), wait) != dones.end()) {
            continue;
        }

        // 处理。
        if (typeid(*wait) == typeid(Relation)) {
            // 如果目标是“关系”，那么就查看关系是否可以运转，
            // 如果不能，就将需要的“对象”放入等待队列中。
            Relation *prlt = (Relation *)wait;
            if (on_meet_rlt(prlt) == false) {
                break;
            }

            for (Relation *prlt : wait->get_rlts()) {
                vector<Object *> needs;

                if (!prlt->can_perform(wait)) {
                    // 这个关系无法运转wait对象，所以放弃！
                    continue;
                }

                if (prlt->perform(needs)) {
                    // 这个关系可以运转得到结果！
                } else {
                    // 这个关系无法运转！
                    if (needs.size() == 0) {
                        // 无法运转是因为“不能”，跳过。
                    } else {
                        // 无法运转是因为有内部对象欠缺，加入栈，看是探索对象！
                        waits.insert(waits.end(), needs.begin(), needs.end());
                    }
                }
            }

            // vector<Object *> needs;
            // if (prlt->perform(needs)) {
            //     // 处理完成！
            // } else

            // // for( auto o : rlt->get_objects()) {
            // //     LOGE("insert o: %s\n", o->get_name().c_str());
            // // }
            // waits.insert(waits.end(), rlt->get_objects().begin(), rlt->get_objects().end());

            // // for( auto o : rlt->get_rlts()) {
            // //     LOGE("insert r: %s\n", o->get_name().c_str());
            // // }
            // // Relation is also a object, so it has relations.
            // waits.insert(waits.end(), rlt->get_rlts().begin(), rlt->get_rlts().end());

        } else {
            // 如果是“对象”，就看是否有值。
            // 如果没有，就看是否通过关联的关系获取！
            if (on_meet_obj(wait) == false) {
                break;
            }

            if (wait->get_value().get_type() != Value::TYPE_NONE) {
                // 有值，返回！
            }

            // 把对象的所有关系都压栈，然后放入到等待队列中。
            waits.insert(waits.end(), wait->get_rlts().begin(), wait->get_rlts().end());

            // for( auto o : wait->get_rlts()) {
            //     LOGE("insert r: %s\n", o->get_name().c_str());
            // }
        }

        // 如果处理过了，就放入到处理过的队列中。
        dones.push_back(wait);

    } while (true);

    return true;
}