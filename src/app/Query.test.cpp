#include <catch.hpp>

#include <Process.hpp>
#include <Query.hpp>

/**
 * 查询是遍历模型，然后根据关系和指令进行计算。
 * TODO: 查询是 Process中可以执行的一个动作，之后可能做成一个"基于结果的关系计算"（relation to Result）。
 */

TEST_CASE("Query", "[app]") {
    ProcessCmdLine process;

    SECTION("create a model and query") {
        REQUIRE(process.exec("Model name=mdl"));

        SECTION("add elments") {
            REQUIRE(process.exec("Element name=eml1"));
            REQUIRE(process.exec("Element name=eml2"));
            REQUIRE(process.exec("Element name=eml3"));

            REQUIRE(process.exec("Relation name=rlt1 from=eml1 to=eml2"));
            REQUIRE(process.exec("Relation name=rlt2 from=eml2 to=eml3"));

            // 这里需要设定查询的语法。
            // TODO: 怎么自动检查查询结果？
            SECTION("query") {
                REQUIRE(process.exec("Query name=q01 value=eml1.rlt1")); // TODO: 应该显示到日志中，但是怎么看到？
                REQUIRE(process.exec("Query name=q02 value=eml2.rlt2"));
                // REQUIRE(process.exec("Query name=q03 value=eml2.~rlt1")); // 反关系
                REQUIRE(process.exec("Query name=q04 value=eml1.rlt3")); // Failed
            }

            // 处理表达式。
            SECTION("logic judge") {
                REQUIRE(process.exec("Query name=q11 value=eml1.rlt2")); // 不存在的关系
                // REQUIRE(process.exec("Query name=q12 value=\"eml1.rlt1==elm3.~rlt2\"")); // “==” 判断。
            }
        }
    }
}