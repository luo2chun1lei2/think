#pragma once

#include <Model.hpp>
#include <Output.hpp>

/**
 * 接受外部输入，然后控制内部的Model、output等组件。
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
 * 用命令行来控制Model和output。
 */
class ProcessCmdLine : public Process
{
public:
	ProcessCmdLine() : Process() {}
	
	virtual ~ProcessCmdLine() {}
	
	virtual void set_model(Model *model) {
		this->model = model;
	}
	virtual void set_output(Output *output) {
		this->output = output;
	}
	
	/**
	 * 分析命令并执行。
	 * @cmd 这里命令是一行，不存在换行问题。
	 * @return false:命令解析失败，不符合语法。不代表执行的结果如何。
	 */
	virtual bool exec(const std::string cmd);
	
protected:
	Model *model;
    Output *output;
private:
};
