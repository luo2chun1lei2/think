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
