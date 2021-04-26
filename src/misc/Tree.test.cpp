#include <catch.hpp>

#include <misc/Tree.hpp>

TEST_CASE("Tree", "[misc]") {
    SECTION("init a tree") {

        TreeNode<int> node_1(new int(0));

        TreeNode<int> node_1_1(new int(0));
        TreeNode<int> node_1_1_1(new int(0));

        TreeNode<int> node_1_2(new int(0));
        TreeNode<int> node_1_2_1(new int(0));
        TreeNode<int> node_1_2_2(new int(0));
        TreeNode<int> node_1_2_3(new int(0));

        TreeNode<int> node_1_2_2_1(new int(0));

        node_1.add_sub(&node_1_1);
        node_1_1.add_sub(&node_1_1_1);
        node_1.add_sub(&node_1_2);
        node_1_2.add_sub(&node_1_2_1);
        node_1_2.add_sub(&node_1_2_2);
        node_1_2_2.add_sub(&node_1_2_2_1);
        node_1_2.add_sub(&node_1_2_2);
        node_1_2.add_sub(&node_1_2_3);

        SECTION("Travel") {
            TreeNode<int>::travel(&node_1);
        }
    }
}