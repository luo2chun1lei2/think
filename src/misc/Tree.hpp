#pragma once

#include <algorithm>
#include <vector>

/**
 * @brief Tree的节点。
 * 每个节点只能有一个附加的数据。
 * 如果子节点是空的，那么就是叶子。
 * 不限制节点的叶子的数目。
 */
template <typename Data>
class TreeNode {
public:
    TreeNode() {
        data = nullptr;
    }

    TreeNode(Data *data) {
        this->data = data;
    }

    virtual ~TreeNode() {
        // don't free data.
    }

    virtual void set_data(Data *data) {
        this->data = data;
    }

    virtual Data *get_data() {
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

    /**
     * @brief 清理自己的内部的所有的子节点，包括更下级相关的子节点。
     * 需要递归，所以需要注意实现的功能。
     */
    virtual void clean_children(bool free_node, bool free_data) {
        for(auto node : children) {
            node->clean_children(free_node, free_data);
            if(free_data) {
                delete this->data;
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

    /**
     * @brief 深度遍历内部的节点。
     */
    static void travel(TreeNode *node);

protected:
    Data *data;
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
void TreeNode<Data>::travel(TreeNode<Data> *node) {
}