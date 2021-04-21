#pragma once

/**
 * @brief 数学计算公式相关的关系都放在这里。
 * 
 */

#include <string>

#include <core/Relation.hpp>

///////////////////////////////////////////////////////////

class RltPlus : public Relation
{
public:
    RltPlus(const std::string name);
    virtual ~RltPlus();

    virtual void set_value(Value value);
    virtual bool perform();

protected:

private:

};

///////////////////////////////////////////////////////////

class RltMinus : public Relation {
public:
    RltMinus(const std::string name);
    virtual ~RltMinus();

    virtual void set_value(Value value);
    virtual bool perform();

protected:

private:

};

///////////////////////////////////////////////////////////

class RltDevide : public Relation
{
public:
    RltDevide(const std::string name);
    virtual ~RltDevide();

    virtual void set_value(Value value);
    virtual bool perform();

protected:

private:

};


///////////////////////////////////////////////////////////

class RltMultiple : public Relation
{
public:
    RltMultiple(const std::string name);
    virtual ~RltMultiple();

    virtual void set_value(Value value);
    virtual bool perform();

protected:

private:
};

///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
