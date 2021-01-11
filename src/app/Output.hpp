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
	OutputGraphviz(const std::string name);
	virtual ~OutputGraphviz();
	virtual void set_output_filepath(const std::string path);
	virtual bool output(const Model *model);
	virtual bool output2(const Model *model);
protected:
	virtual bool prepare_graphviz();
	virtual void finish_graphviz();
	virtual void finish_graphviz2();
	
	std::string output_file_path;
	Agraph_t *g;
	GVC_t *gvc;

private:
};
