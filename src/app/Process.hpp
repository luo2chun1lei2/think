#pragma once

/**
 * @file
 * @brief 处理脚本等事物。
 */

#include <string>

#include <misc/Misc.hpp>
#include <app/Model.hpp>

/**
 * 根据外部传入的命令，执行
 */
class Process
{
public:
	virtual bool exec(const std::string cmd) = 0;
protected:
private:
};

class ProcessCmdLine : public Process
{
public:
	ProcessCmdLine() {
		model = nullptr;
	}

	// model被内部管理，外部不负责删除。
	ProcessCmdLine(Model *model) {
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
     * @brief 处理一个脚本文件。
     * 
     * @param script_path 
     * @return true 
     * @return false 
     */
    bool exec_script(std::string script_path);
		
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
	bool init_all_properties(std::string obj_name, ParseCommandLineWithProperties::Properties properties);
/*	bool output_graphviz(const std::string name, ParseCommandLineWithProperties &parse);
*/
private:
};
