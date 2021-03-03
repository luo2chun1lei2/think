#pragma once

#include <Model.hpp>
#include <Output.hpp>
#include <Misc.hpp>

/**
 * 作为容纳对于model的处理的对象，将外部的app和对于model的处理分离开。
 * 比如接受外部输入，然后控制内部的Model、output等组件。
 * TODO: 后面也做成Element。
 */
class Process
{
public:
	Process() {}
	virtual ~Process() {}
protected:
private:
};


/**
 * 包含一个Model，然后用命令行来控制Model。
 */
class ProcessCmdLine : public Process
{
public:
	ProcessCmdLine() : Process() {
		model = nullptr;
	}

	// model被内部管理，外部不负责删除。
	ProcessCmdLine(Model *model) : Process() {
		this->model = model;
	}
	
	virtual ~ProcessCmdLine() {
		if (model) {
			delete model;
		}
	}
	
	// model被内部管理，外部不负责删除。
	virtual void set_model(Model *model) {
		if (this->model)
			delete this->model;
		this->model = model;
	}
		
	/**
	 * 分析命令并执行。
	 * @cmd 这里命令是一行，不存在换行问题。
	 * @return false:命令解析失败，不符合语法。不代表执行的结果如何。
	 */
	virtual bool exec(const std::string cmd);
	
protected:
	// 当前只有一个model。
	Model *model;

	// 根据来自commandline的properties设置elm的内部属性。
	bool init_all_properties(Element * elm, ParseCommandLineWithProperties::Properties properties);
	bool output_graphviz(const std::string name, ParseCommandLineWithProperties &parse);

private:
};

bool exec_script(const char *script_path);
