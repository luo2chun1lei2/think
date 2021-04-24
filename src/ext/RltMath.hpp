#pragma once

/**
 * @brief 数学计算公式相关的关系都放在这里。注意不是运算。
 * expression 是表达式， equation是工程式，Identity是恒等式，Formula是普遍规律的公式。
 */

#include <string>

#include <core/Relation.hpp>

///////////////////////////////////////////////////////////

class RltPlus : public Relation {
public:
    RltPlus(const std::string name);
    virtual ~RltPlus();

    virtual void set_value(Value value);

    virtual bool can_perform(const Object *pobj) const;
    virtual std::vector<Object *> get_objs_need_value() const;
    virtual bool perform(std::vector<Object *> &need_objs);

protected:
private:
};

///////////////////////////////////////////////////////////

class RltMinus : public Relation {
public:
    RltMinus(const std::string name);
    virtual ~RltMinus();

    virtual void set_value(Value value);

    //virtual bool can_perform(const Object *pobj) const;
    //virtual std::vector<Object *> get_objs_need_value() const;
    virtual bool perform(std::vector<Object *> &need_objs);

protected:
private:
};

///////////////////////////////////////////////////////////

class RltDevide : public Relation {
public:
    RltDevide(const std::string name);
    virtual ~RltDevide();

    virtual void set_value(Value value);

    virtual bool can_perform(const Object *pobj) const;
    virtual std::vector<Object *> get_objs_need_value() const;
    virtual bool perform(std::vector<Object *> &need_objs);

protected:
private:
};

///////////////////////////////////////////////////////////

class RltMultiple : public Relation {
public:
    RltMultiple(const std::string name);
    virtual ~RltMultiple();

    virtual void set_value(Value value);

    //virtual bool can_perform(const Object *pobj) const;
    //virtual std::vector<Object *> get_objs_need_value() const;
    virtual bool perform(std::vector<Object *> &need_objs);

protected:
private:
};

///////////////////////////////////////////////////////////

class RltEqual : public Relation {
public:
    RltEqual(const std::string name);
    virtual ~RltEqual();

    virtual void set_value(Value value);

    virtual bool can_perform(const Object *pobj) const;
    virtual std::vector<Object *> get_objs_need_value() const;
    virtual bool perform(std::vector<Object *> &need_objs);

protected:
private:
};

///////////////////////////////////////////////////////////
