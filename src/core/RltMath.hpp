#pragma once

/**
 * @brief 数学计算公式相关的关系都放在这里。注意不是运算。
 * expression 是表达式， equation是工程式，Identity是恒等式，Formula是普遍规律的公式。
 */

#include <string>

#include <core/Object.hpp>
#include <core/Relation.hpp>
#include <core/ObjValue.hpp>

class RltMathOperation : public Relation
{
public:
    RltMathOperation(const std::string name);
    virtual ~RltMathOperation();

    virtual void set_value(Value value);

    virtual std::vector<Object *> get_objs_need_value() const;
    virtual bool perform(std::vector<Object *> &need_objs) = 0;

protected:
private:
};

///////////////////////////////////////////////////////////

class RltPlus : public RltMathOperation {
public:
    RltPlus(const std::string name);
    virtual ~RltPlus();

    virtual bool can_perform(const Object *pobj) const;
    virtual bool perform(std::vector<Object *> &need_objs);

protected:
private:
};

///////////////////////////////////////////////////////////

class RltMinus : public RltMathOperation {
public:
    RltMinus(const std::string name);
    virtual ~RltMinus();

    //virtual bool can_perform(const Object *pobj) const;
    //virtual std::vector<Object *> get_objs_need_value() const;
    virtual bool perform(std::vector<Object *> &need_objs);

protected:
private:
};

///////////////////////////////////////////////////////////

class RltDevide : public RltMathOperation {
public:
    RltDevide(const std::string name);
    virtual ~RltDevide();

    virtual bool can_perform(const Object *pobj) const;
    virtual bool perform(std::vector<Object *> &need_objs);

protected:
private:
};

///////////////////////////////////////////////////////////

class RltMultiple : public RltMathOperation {
public:
    RltMultiple(const std::string name);
    virtual ~RltMultiple();

    //virtual bool can_perform(const Object *pobj) const;
    //virtual std::vector<Object *> get_objs_need_value() const;
    virtual bool perform(std::vector<Object *> &need_objs);

protected:
private:
};

///////////////////////////////////////////////////////////

class RltEqual : public RltMathOperation {
public:
    RltEqual(const std::string name);
    virtual ~RltEqual();

    virtual bool can_perform(const Object *pobj) const;
    virtual std::vector<Object *> get_objs_need_value() const;
    virtual bool perform(std::vector<Object *> &need_objs);

protected:
private:
};

///////////////////////////////////////////////////////////
