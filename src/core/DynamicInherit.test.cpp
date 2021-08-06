#include <catch.hpp>

#include <core/DynamicInherit.hpp>

/**
 * 凡是继承了 DynamicClass 的类型，都可以自动添加 Object 类型。
 */
class DynamicClass {
public:
protected:
private:
};

/**
 * Object的动态类型的模板，描述了一个Object类型都有什么样的关系。
 */
class DynamicClassTemplate {
public:
protected:
private:
}; 

/**
 * 工厂可以根据模板来生成一个符合标准的实例。
 */
class DynamicClassFactory {
public:
    bool make(DynamicClass * instance, const DynamicClassTemplate & tpl) {return false;}
protected:
private:
};

/**
 * 检查对象实例是否符合类型的要求。
 */
class DynamicClassCheck {
public:
    DynamicClassCheck(const DynamicClassTemplate &tpl) {}
    bool check(const DynamicClass & instance) {return false;}
protected:
private:
};

/**
 * 动态的类型继承。
 * 1. 一个实例可以在运行时成为一个类型。
 * 2. 类型的检查是用“限制或检查”来实现的。显示是描述，检查是具体方法。
 * 3. 类型的生成可以用“模板或工厂”来实现。模板是描述，工厂是实现的方法。
 */

TEST_CASE("DynamicInherit", "[core][new]") {

    // 可以动态变化Object类型的类。
    class ABC : public DynamicClass
    {
    public:
    protected:
    private:
    };

    SECTION("create a dynamic class") {
        ABC abc;
        DynamicClassTemplate tpl;
        DynamicClassFactory factory;

        REQUIRE(factory.make(&abc, tpl));

        SECTION("check a dynamic class") {
            DynamicClassCheck check(tpl);

            REQUIRE(check.check(abc));
        }
    }

    
}