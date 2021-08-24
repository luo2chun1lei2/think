#include <catch.hpp>

#include <core/DynamicInterface.hpp>

using namespace std;

/**
 * 目标是：
 * 1. 实例在创建时，可以添加一个实现，这个实现可以被查询，然后调用，实现具体的功能。
 */

TEST_CASE("DynamicInterface", "[core]") {

    class Interface {};

    class Interfaces;

    

    class Interfaces {
    public:
        Interfaces(DynamicInterface * dynamic)
        {
            _dynamic = dynamic;
        }

        void add_impl(std::string id) { // TODO need ?
        }

        bool has_impl(std::string id) {
            _dynamic->on_di_query_name();
        }

    private:
        DynamicInterface * _dynamic;
    };

    class DynamicInterface {
    public:
        DynamicInterface() {
            _interfaces = new Interfaces(this);
        }
        virtual ~DynamicInterface() {
        }

        Interfaces *interfaces() {
            return this->_interfaces;
        }
    
        bool on_di_query_name()
        {
            return true;
        }

    protected:
        Interfaces * _interfaces;

    private:
    };

    class One : public DynamicInterface {
    public:
        const std::string get_name() {
            return "xiao ming";
        }

    protected:
    private:
        std::string _name;
    };

    SECTION("define a dynamic class and add interface.") {
        One one;

        // 添加了一个实现
        //one.interfaces().add_impl("IName", Interface("IName"));
        //REQUIRE();

        // 或许实现，并且调用！
        REQUIRE(one.interfaces()->has_impl("IName"));
        REQUIRE(one.interfaces()->has_impl("IValue") == false);

        Interface *intf = dynamic_cast<Interface *> one.interfaces().get_impl("IName");
        REQUIRE(intf != NULL);
        REQUIRE(intf.get_name() == "xiao ming");
    }

    class Value : public DynamicInterface {};

    SECTION("define a dynamic class and add interface.") {
    }
}
