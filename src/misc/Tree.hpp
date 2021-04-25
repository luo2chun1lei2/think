#pragma once

#include <vector>

/**
 * @brief Tree的节点。
 * 每个节点只能有一个附加的数据。
 * 如果子节点是空的，那么就是叶子。
 * 不限制节点的叶子的数目。
 */
template <typename Data> class TreeNode {
public:
    TreeNode();
    TreeNode(Data *data);
    virtual ~TreeNode();

    virtual void set_data(Data *data);
    virtual Data *get_data();

    virtual void add_sub(TreeNode<Data> *node);
    // 将节点和此节点的子节点都从Tree拿出来，但是不会释放任何资源。
    virtual TreeNode<Data> *remove_sub(TreeNode<Data> *node);
    virtual std::vector<TreeNode<Data> *> get_subs();

    virtual void set_parent(TreeNode<Data> *);
    virtual TreeNode<Data> *get_parent();

    virtual void travel(TreeNode<Data> *node);

    /**
     * @brief 清理自己的内部的所有的子节点，包括更下级相关的子节点。
     */
    virtual void clean(bool free_node, bool free_data);

    /**
     * @brief 静态函数，方便清理所有的节点，包括根。
     * 可能释放 node 节点的数据和节点本身。
     */
    static void clean(TreeNode<Data> *node, bool free_node, bool free_data);

protected:
    Data *data;
    std::vector<TreeNode<Data> *> subs;
    TreeNode *parent;

private:
};
