#include <ext/Perform.hpp>

#include <algorithm>

#include <misc/Misc.hpp>

using namespace std;

///////////////////////////////////////////////////////////

PerformRound::MyTravel::MyTravel(bool log)
    : Travel(log) {
    end = false;
}

bool PerformRound::MyTravel::is_end() {
    return end;
}

bool PerformRound::MyTravel::travel(Object *pobj) {
    target = pobj;
    bool rtn = Travel::travel(pobj);

    // 无法再运转更多的对象，所以必须退出。
    if (cur_oks.size() == last_oks.size()) {
        end = true;
    } else {
        last_oks.clear();
        last_oks.insert(last_oks.end(), cur_oks.begin(), cur_oks.end());
        cur_oks.clear();
    }

    return rtn;
}

bool PerformRound::MyTravel::on_meet_obj(Object *pobj) {
    return true;
}

bool PerformRound::MyTravel::on_meet_rlt(Relation *prlt) {
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

///////////////////////////////////////

PerformRound::PerformRound(int max_round) {
    this->max_round = max_round;
}

PerformRound::~PerformRound() {
}

bool PerformRound::perform(Object *pobj) {

    MyTravel my_travel(false);
    do {
        my_travel.travel(pobj);
    } while (!my_travel.is_end() && (max_round == -1 || --max_round > 0));

    if (pobj->get_value().get_type() == Value::TYPE_NONE) {
        return false;
    }

    return true;
}

///////////////////////////////////////////////////////////

PerformEffectTree::PerformEffectTree() {
}

PerformEffectTree::~PerformEffectTree() {
}

bool PerformEffectTree::on_meet_obj(Object *pobj) {
    return true;
}

bool PerformEffectTree::on_meet_rlt(Relation *prlt) {
    return true;
}

/**
 * 原理：
 * 1. 如果是关系：是无法具有值的，退出。
 * 2. 如果是对象：看自己是否有值，然后看相关关系是否可以运转自己的值。
 *   如果相关关系可以计算，但是有欠缺的对象，那么查找对象的相关关系。
 *
 * 算法：
 * 1. 目标是关系，则返回错误。
 * 2. 否则查找目标（是非关系的对象）的相关关系。
 * 3. 如果此关系无法影响对象，则忽略。
 * 4. 可以影响此对象，则找此关系的相关对象。跳转到2，
 * 5. 如果没有可以查找的对象，那么此影响树形成。
 *
 * 影响树，父节点是被影响对象，下层节点是影响它的关系，关系的下层对象是影响的对象。
 *
 * 1. 按照深度遍历方法，从根节点开始找到叶子，然后回退，碰到关系就运转。
 *   如果失败，就打出关联的Path。
 */
bool PerformEffectTree::perform(Object *pobj) {
    // 记录已经遍历后的对象。
    vector<Object *> dones;

    // 记录还没有遍历的对象。
    vector<Object *> waits;

    waits.push_back(pobj);

    vector<Object *> affect_tree;

    ///////////////////////////////////
    // 形成影响树(Affect Tree)。
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
        Relation *prlt = dynamic_cast<Relation *>(wait);
        if (prlt) {
            // 如果目标是“关系”，那么就查看关系是否可以运转，
            // 如果不能，就将需要的“对象”放入等待队列中。

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

    ///////////////////////////////////
    // 遍历影响树

    return true;
}