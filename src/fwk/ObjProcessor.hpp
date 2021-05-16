#pragma once

#include <core/Object.hpp>

#include <string>

/**
 * @brief 执行一行一行的命令。
 */
class ObjProcessorLine : public Object
{
public:
    ObjProcessorLine(const std::string name);
    virtual ~ObjProcessorLine();

    virtual bool begin_notify();
    virtual bool notify(Object *obj);
    virtual bool end_notify();
protected:
private:
};