#pragma once

#include <core/Object.hpp>

#include <string>

#include <stdio.h>

/**
 * 可以遍历文件的每一行的对象。
 * 1. 只输出，不输入。
 * 2. 需要设定文件的路径。
 * @property path:<string>
 */
class FileLine : public Object
{
public:
    FileLine(const std::string name);
    virtual ~FileLine();

    ///////////////////////////////////////////////////////
    // 根据通知，同步
    
    // 通知开始
    virtual bool begin_notify();
    // 通知都有哪些对象。
    virtual bool notify(Object *obj);
    // 通知结束，绘制并显示结果。
    virtual bool end_notify();

    ///////////////////////////////////////////////////////
    // 可以设置的属性
    virtual void set_path(const std::string path);

    ///////////////////////////////////////////////////////
    // 获取数据

    /**
     * 读取文件的一行数据。
     * 1. 文件读取失败。
     * 2. 超出文件结尾。
     * 3. 正常结果。
     * @param index -1: 继续下一个
     */
    virtual const std::string get_line(int index, bool &is_end, bool &is_error);

protected:
    std::string _path;
    FILE * _fp;
private:
};
