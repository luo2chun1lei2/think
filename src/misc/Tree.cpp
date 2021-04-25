#include <misc/Tree.hpp>

#include <algorithm>

#include <misc/Misc.hpp>

using namespace std;

template <typename Data>
TreeNode<Data>::TreeNode() {
    data = nullptr;
}

template <typename Data>
TreeNode<Data>::TreeNode(Data *data) {
    this->data = data;
}

template <typename Data>
TreeNode<Data>::~TreeNode() {
    // don't free data.
}

template <typename Data>
void TreeNode<Data>::set_data(Data *data) {
    this->data = data;
}

template <typename Data>
Data *TreeNode<Data>::get_data() {
    return this->data;
}

template <typename Data>
void TreeNode<Data>::add_sub(TreeNode<Data> *node) {
    if (std::find(subs.begin(), subs.end(), node) != subs.end())
        return;

    this->subs.push_back(node);
    node->set_parent(this);
}

template <typename Data>
TreeNode<Data> *TreeNode<Data>::remove_sub(TreeNode<Data> *node) {

    for (auto iter = subs.begin(); iter != subs.end(); iter++) {
        if (*iter == node) {
            this->subs.erase(iter);
            *iter->parent = nullptr;
            return *iter;
        }
    }

    return nullptr;
}

template <typename Data>
std::vector<TreeNode<Data> *> TreeNode<Data>::get_subs() {
    return this->subs;
}

template <typename Data>
void TreeNode<Data>::set_parent(TreeNode<Data> *node) {
    this->parent = node;
}

template <typename Data>
TreeNode<Data> *TreeNode<Data>::get_parent() {
    return this->parent;
}

template <typename Data>
void travel(TreeNode<Data> *node) {
}

template <typename Data>
void TreeNode<Data>::clean(bool free_node, bool free_data) {
}

template <typename Data>
void TreeNode<Data>::clean(TreeNode<Data> *node, bool free_node, bool free_data) {
    node->clean(free_node, free_data);

    if (free_data) {
        delete node->data;
    }

    if (free_node) {
        delete free_node;
    }
}