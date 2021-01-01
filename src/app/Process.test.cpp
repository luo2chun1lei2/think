#include <catch.hpp>

#include <Process.hpp>

/**
 * 输入可以是挺多的种类，首先实现API调用（Model的接口就是），
 * 然后是命令行调用API，特点是美哦一
 * 之后是纯描述关系的语句。
 */

TEST_CASE("control about comand line", "[app][block]") {

    ProcessCmdLine process;

    SECTION("create a model and output") {
        REQUIRE(process.exec("Model name=mdl"));
        

        SECTION("add elments") {
            REQUIRE(process.exec("Element name=eml1"));
            REQUIRE(process.exec("Element name=eml2"));
            REQUIRE(process.exec("Element name=eml3"));

            SECTION("add relation") {
                REQUIRE(process.exec("Relation name=rlt1 from=eml1 to=eml2"));
                REQUIRE(process.exec("Relation name=rlt2 from=eml2 to=eml3"));
/*
                // 这里需要设定查询的语法。
                SECTION("query") {
                    REQUIRE(process.exec("Query name=q01 value=eml1.rlt1")); // 应该显示到日志中，但是怎么看到？
                    REQUIRE(process.exec("Query name=q02 value=eml2.rlt2"));
                    REQUIRE(process.exec("Query name=q03 value=eml2.~rlt1")); // 反关系
                    REQUIRE(!process.exec("Query name=q04 value=eml1.rlt3")); // Failed
                }

                // 处理表达式。
                SECTION("逻辑判断") {
                    REQUIRE(process.exec("Query name=q11 value=eml1.rlt2"));  // 不存在的关系
                    REQUIRE(process.exec("Query name=q12 value=\"eml1.rlt1==elm3.~rlt2\"")); // “==” 判断。
                }

                SECTION("clear") {
                    REQUIRE(process.exec("Clear")); // 没有名字，所以是临时对象，用完就释放
                }   */
                
                SECTION("output") {
                    REQUIRE(process.exec("Output name=out")); // output 是动作！
                }
            }
        }
    }
}
