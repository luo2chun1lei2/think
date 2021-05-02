#include <catch.hpp>

#include <string>

#include <misc/Misc.hpp>
#include <misc/Tree.hpp>

using namespace std;

TEST_CASE("Tree", "[misc]") {
    SECTION("init a tree") {

        TreeNode<string> node_1(string("1"));

        TreeNode<string> node_1_1(string("1.1"));
        TreeNode<string> node_1_1_1(string("1.1.1"));

        TreeNode<string> node_1_2(string("1.2"));
        TreeNode<string> node_1_2_1(string("1.2.1"));
        TreeNode<string> node_1_2_2(string("1.2.2"));
        TreeNode<string> node_1_2_3(string("1.2.3"));

        TreeNode<string> node_1_2_2_1(string("1.2.2.1"));

        node_1.add_sub(&node_1_1);
        node_1_1.add_sub(&node_1_1_1);
        node_1.add_sub(&node_1_2);
        node_1_2.add_sub(&node_1_2_1);
        node_1_2.add_sub(&node_1_2_2);
        node_1_2_2.add_sub(&node_1_2_2_1);
        node_1_2.add_sub(&node_1_2_2);
        node_1_2.add_sub(&node_1_2_3);

        SECTION("TravelPreorder") {
            vector<string> path;
            TreeNode<string>::travelByPreorder(&node_1,
                                               [&path](TreeNode<string> *node) { path.push_back(node->get_data()); });

            REQUIRE(path.size() == 8);
            REQUIRE(path[0] == "1");
            REQUIRE(path[1] == "1.1");
            REQUIRE(path[2] == "1.1.1");
            REQUIRE(path[3] == "1.2");
            REQUIRE(path[4] == "1.2.1");
            REQUIRE(path[5] == "1.2.2");
            REQUIRE(path[6] == "1.2.2.1");
            REQUIRE(path[7] == "1.2.3");
        }

        SECTION("TravelPostorder") {
            vector<string> path;
            TreeNode<string>::travelByPostorder(&node_1,
                                                [&path](TreeNode<string> *node) { path.push_back(node->get_data()); });

            REQUIRE(path.size() == 8);
            REQUIRE(path[0] == "1.1.1");
            REQUIRE(path[1] == "1.1");
            REQUIRE(path[2] == "1.2.1");
            REQUIRE(path[3] == "1.2.2.1");
            REQUIRE(path[4] == "1.2.2");
            REQUIRE(path[5] == "1.2.3");
            REQUIRE(path[6] == "1.2");
            REQUIRE(path[7] == "1");
        }
    }
}