#!/bin/bash

# 这里会加入测试脚本，主要是
# 1. 从外部测试整个程序，比如测试命令行的参数。
# 2. 测试从外部执行脚本。
# 3. 测试交互模式下的脚本。

2021/08/09 设想的语言：

规定: 小写的是实例
      大写的是类型(某种类型)
    r/s/t 一般是关系的实例，R是关系的类型。
    a/b/c 一般是对象的实例，O是关系的类型。

1. 简单的语句
(x, y, z, ...) = r(a, b, c, ...)        # 关系设置方法
a.r = (x, y, z, ...)                    # 属性设置方法

Date birthday = String("2021/1/2")

2. OR-Net
(x1, y1, z1, ...) = r1(a1, b1, c1, ...)
(x2, y2, z2, ...) = r2(a2, b2, c2, ...)
(x3, y3, z3, ...) = r3(a3, b3, c3, ...)

3. Type = Factory
# 当做一个对象，可以有自己的属性。
Object Person (String name, Int age, Date birthday, Float height, Float weight)
{
    ._name = name
    ._age = age
    ._birthday = birthday
    ._height = height
    ._weight = weight
}
# 其实就是通过工厂模式，给自己这个对象加入特定的属性。
Person p1("luocl", 32, "1988/8/8", 170, 80)

# 当做一个新的关系，内部隐藏了复杂的关系说明。
# c^2 = a ^ 2 + b ^2;
Relation S(Float a, Float b) as (Float c)
{
    d = sum(a^2, b^2)
    c = sqrt(d)
}
# 其实就是通过工厂模式，本关系内部的关系设置。
# TODO: 普通语言中，也没有function的具体实例，而是只有一个类型，内含一个实例。
# s.from = a&b, s.to = c
c = S(a, b)

4. Check
# 根据type来判断对象是否符合要求。
true == Check(b, B) # 检查b的内部属性，是否符合B的要求。
true == Check(s, S) # 检查s的相关a、b、c之间的关系是否符合s的要求。