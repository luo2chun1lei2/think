#pragma once

#include <string>

#include <graphviz/gvc.h>

#include <Model.hpp>

/**
 * 将Model导出
 * TODO: 后面也做成Element。
 */
class Output
{
public:
	Output(const std::string name) {}
	virtual ~Output() {}
	virtual bool output(const Model *model) = 0;
protected:
private:
};

/**
 * 将Model导出到Graphviz
 */
class OutputGraphviz : public Output
{
public:
	enum Option {
		GRAPH_SVG = 0x1,	// 显示为SVG文件
		GRAPH_TEXT = 0x2,	// 显示为dot用的TEXT
	};

	enum Type {
		TYPE_BASIC = 0x0,	// 最基本的图
		TYPE_LIST = 0x1,	// 列表类型
		TYPE_CALL = 0x2,	// 调用关系，比如函数调用。首先是调用关系，然后才是包含结构。
		TYPE_LAYOUT = 0x3,	// 层级关系的，比如系统架构图。首先包含结构，然后才是调用关系。
	};

	OutputGraphviz(const std::string name, OutputGraphviz::Option option, OutputGraphviz::Type type);
	virtual ~OutputGraphviz();
	virtual void set_output_filepath(const std::string path);
	virtual bool output(const Model *model);

protected:
	virtual bool prepare_graphviz();
	virtual void finish_graphviz();

	std::string output_file_path;
	Option option;
	Type type;

	Agraph_t *g;
	GVC_t *gvc;

private:
};
