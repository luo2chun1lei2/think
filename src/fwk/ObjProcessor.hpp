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
	virtual void set_model(Model *model) {
		if (this->_model)
			delete this->_model;
		this->_model = model;
	}

protected:

    virtual bool exec(const std::string cmd);
    virtual bool output_graphviz(const std::string name, ParseCommandLineWithProperties &parse);
    virtual bool init_all_properties(std::string obj_name, ParseCommandLineWithProperties::Properties properties);

    // 当前只有一个model。
	Model *_model;

private:
};