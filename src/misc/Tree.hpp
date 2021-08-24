#pragma once

#include <algorithm>
#include <functional>
#include <vector>

/**
 * @brief Tree的节点。
 * 每个节点只能有一个附加的数据。
 * 如果子节点是空的，那么就是叶子。
 * 不限制节点的叶子的数目。
 * 
 * 这里的算法，主要是解决关系的执行问题，主要是后序。
 * 
 * Data 是TreeNode所持有的数据的类型。
 */
template <typename Data>
class TreeNode {
public:
    TreeNode() {
        parent = nullptr;
        data = nullptr;
    }

    TreeNode(Data data) {
        parent = nullptr;
        this->data = data;
    }

    virtual ~TreeNode() {
        // don't free data.
    }

    virtual void set_data(Data data) {
        this->data = data;
    }

    virtual Data get_data() {
        return this->data;
    }

    virtual void add_sub(TreeNode *node) {
        if (std::find(children.begin(), children.end(), node) != children.end())
            return;

        this->children.push_back(node);
        node->set_parent(this);
    }

    // 将节点和此节点的子节点都从Tree拿出来，但是不会释放任何资源。
    virtual TreeNode *remove_sub(TreeNode *node) {

        for (auto iter = children.begin(); iter != children.end(); iter++) {
            if (*iter == node) {
                this->children.erase(iter);
                (*iter)->parent = nullptr;
                return *iter;
            }
        }

        return nullptr;
    }

    virtual std::vector<TreeNode *> get_children() {
        return this->children;
    }

    virtual void set_parent(TreeNode * node) {
        this->parent = node;
    }

    virtual TreeNode *get_parent() {
        return this->parent;
    }

    // 判断自己父节点的最后子节点
    // 如果没有父节点， return true
    virtual bool self_is_last_child() {
        if (!parent) {
            return true;
        }

        if (parent->get_children().back() == this) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief 清理自己的内部的所有的子节点，包括更下级相关的子节点。
     * 需要递归，所以需要注意实现的功能。
     * TODO: free_data 应该变成 匿名函数。
     */
    virtual void clean_children(bool free_node, bool free_data) {
        for(auto node : children) {
            node->clean_children(free_node, free_data);
            if(free_data) {
                //delete this->data;
            }

            if (free_node) {
                delete node;
            }
        }
        children.clear();
    }

    /**
     * @brief 静态函数，方便清理所有的节点，包括node。
     * 可能释放 node 节点的数据和节点本身。
     */
    static void clean(TreeNode *node, bool free_node, bool free_data);

    /// 遍历的算法，参考二叉树的preorder/inorder/postorder三个算法，
    /// 只取了两个算法
    /// preorder: 先处理根，再从左到右，处理子树。
    /// postorder: 先从左到右，处理子树后，再处理根。
    /// TODO: 这里没有看《图论》的图遍历算法，后面需要再参考后修改。
    
    /**
     * @brief 先序遍历内部的节点。
     */
    //static void travelByPreorder(TreeNode *node);
    static void travelByPreorder(TreeNode *root_node, std::function<void (TreeNode*)> const &process);

    /**
     * @brief 后序遍历内部的节点。
     */
    static void travelByPostorder(TreeNode *root_node, std::function<void (TreeNode*)> const &process);

protected:
    Data data;
    std::vector<TreeNode *> children;
    TreeNode *parent;

private:
};

template <typename Data>
void TreeNode<Data>::clean(TreeNode<Data> *node, bool free_node, bool free_data) {
    node->clean_children(free_node, free_data);

    if (free_data) {
        delete node->data;
    }

    if (free_node) {
        delete free_node;
    }
}

template <typename Data>
void TreeNode<Data>::travelByPreorder(TreeNode<Data> *root_node, std::function<void (TreeNode<Data>*)> const &process) {
    std::vector<TreeNode<Data> *> stack;

    stack.push_back(root_node);

    while(stack.size() != 0) {

        // node <- pop stack
        TreeNode<Data> *node = stack.back();
        stack.pop_back();

        // 处理节点
        process(node);

        std::vector<TreeNode<Data>*> children = node->get_children();
        std::reverse(children.begin(), children.end());

        // 放入节点的子节点。
        if (children.size() != 0) {
            for(auto sub : children) {
                stack.push_back(sub);
            }
        } 

    }
}

template <typename Data>
void TreeNode<Data>::travelByPostorder(TreeNode<Data> *root_node, std::function<void (TreeNode<Data>*)> const &process) {
    std::vector<TreeNode<Data> *> stack;
    bool is_last = false;

    stack.push_back(root_node);

    while(stack.size() != 0) {

        // 最后一个节点
        TreeNode<Data> *node = stack.back();
    
        // 1 如果此节点还有子树
        // 1.1 如果之前的子树都处理后，就处理，然后出栈。
        // 1.2 否则，子树就放入节点
        // 2 如果此节点没有子树，就处理，然后出栈。

        std::vector<TreeNode<Data>*> children = node->get_children();
        std::reverse(children.begin(), children.end());

        if (children.size() == 0) {
            process(node);
            // 判断此节点是否是父节点的最后一个节点，这样处理完了，需要处理父节点了。
            is_last = node->self_is_last_child();
            stack.pop_back();
        } else { // 还有子节点
            if (is_last) {
                process(node);
                is_last = node->self_is_last_child();
                stack.pop_back();
            } else {
                for(auto sub : children) {
                    stack.push_back(sub);
                }
            }
        }
    }
} 