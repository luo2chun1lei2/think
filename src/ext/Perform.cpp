#include <ext/Perform.hpp>

#include <algorithm>

#include <ext/Travel.hpp>
#include <misc/Misc.hpp>
#include <misc/Tree.hpp>

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

PerformAffectedTree::PerformAffectedTree() {
}

PerformAffectedTree::~PerformAffectedTree() {
}

bool PerformAffectedTree::on_meet_obj(Object *pobj) {
    return true;
}

bool PerformAffectedTree::on_meet_rlt(Relation *prlt) {
    return true;
}

class Travel1 : public Travel {
public:
    Travel1(TreeNode<Object *> *root_node)
        : root_node(root_node) {
        last_rlt = nullptr;
        last_obj = nullptr;
    }

protected:
    virtual bool on_meet_obj(Object *pobj) {
        if (last_rlt == nullptr) {
            // 根节点。
            root_node->set_data(pobj);
            last_obj = root_node;
        } else {
            last_obj = new TreeNode<Object *>(pobj);
            last_rlt->add_sub(last_obj);
        }
        return true;
    }

    virtual bool on_meet_rlt(Relation *prlt) {
        last_rlt = new TreeNode<Object *>(prlt);
        last_obj->add_sub(last_rlt);
        return true;
    }

private:
    TreeNode<Object *> *last_rlt;
    TreeNode<Object *> *last_obj;

    TreeNode<Object *> *root_node;
};

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
bool PerformAffectedTree::perform(Object *pobj) {
    // 根据相关性得到Tree。
    TreeNode<Object *> tree_root;
    Travel1 travel(&tree_root);
    travel.travel(pobj);

    // 用Tree分析“执行路径”。
    vector<Object *> path;
    TreeNode<Object *>::travelByPostorder(&tree_root,
                                          [&path](TreeNode<Object *> *node) { path.push_back(node->get_data()); });

    // 最后根据路径来计算。
    for (Object *obj : path) {
        Relation *rlt = dynamic_cast<Relation *>(obj);
        if (rlt) {
            vector<Object *> needs;
            // TODO: 返回值
            rlt->perform(needs);
        } else {
            // TODO: 检查object
        }
    }

    // 回收资源
    tree_root.clean_children(true, false);

    return true;
}
