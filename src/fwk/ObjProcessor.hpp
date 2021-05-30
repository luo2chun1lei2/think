#pragma once

#include <core/Object.hpp>
#include <fwk/Model.hpp>
#include <misc/Misc.hpp>

#include <string>

/**
 * @brief 执行一行一行的命令。
 */
class ObjProcessorLine : public Object
{
public:
    ObjProcessorLine(const std::string name);
    ObjProcessorLine(const std::string name, Model *model);
    virtual ~ObjProcessorLine();

    virtual bool begin_notify();
    virtual bool notify(Object *obj);
    virtual bool end_notify();

    // TODO: 是否保留这个接口？
    // model被内部管理，外部不负责删除。
	virtual void set_model(Model *model);

protected:

    virtual bool exec(const std::string cmd);
    virtual bool output_graphviz(const std::string name, ParseCommandLineWithProperties &parse);
    virtual bool init_all_properties(std::string obj_name, ParseCommandLineWithProperties::Properties properties);

    virtual void show_help(void);
    virtual void quit(void);
    virtual bool do_inner_cmd(const std::string line);
    /**
     * @return true 分析过了，false 不需要分析。
     */
    virtual bool parse_inner_cmd(const std::string line);

    // 当前只有一个model。
	Model *_model;

private:
};
