#include <catch.hpp>

#include <core/DynamicInterface.hpp>

using namespace std;

/**
 * 目标是：
 * 1. 实例在创建时，可以添加一个实现，这个实现可以被查询，然后调用，实现具体的功能。
 */

TEST_CASE("DynamicInterface", "[core]") {

    class InterfaceName: public Interface {
    public:
        virtual std::string get_name() = 0;
        virtual void set_name(std::string name) = 0;
    };

    class One : public DynamicInterface {
    public:

        class InnerName : public InterfaceName {
        public:
            InnerName(One *one) {
                _one = one;
            }
            virtual std::string get_name() {
                return _one->_name;
            }
            virtual void set_name(std::string name) {
                _one->_name  = name;
            }

            One *_one;
        };

        One(const std::string name) {
            _name = name;

            _interfaces->add_impl("IName", new InnerName(this));
        }

    protected:
        std::string _name;
    private:
        
    };

    SECTION("define a dynamic class and add interface.") {
        One one("one");

        // 添加了一个实现
        //one.interfaces().add_impl("IName", Interface("IName"));
        //REQUIRE();

        // 或许实现，并且调用！
        REQUIRE(one.interfaces()->has_impl("IName"));
        REQUIRE(one.interfaces()->has_impl("IValue") == false);

        InterfaceName *intf = dynamic_cast<InterfaceName *> (one.interfaces()->get_impl("IName"));
        REQUIRE(intf != NULL);

        REQUIRE(intf->get_name() == "one");
        intf->set_name("xiao ming");
        REQUIRE(intf->get_name() == "xiao ming");
    }

    class Value : public DynamicInterface {};

    SECTION("Interface is set/get value.") {
    }
}
