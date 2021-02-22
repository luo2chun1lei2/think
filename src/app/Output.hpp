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
	enum Options {
		GRAPH_SVG = 0x1,
		GRAPH_TEXT = 0x2,
	};

	OutputGraphviz(const std::string name, OutputGraphviz::Options options);
	virtual ~OutputGraphviz();
	virtual void set_output_filepath(const std::string path);
	virtual bool output(const Model *model);

protected:
	virtual bool prepare_graphviz();
	virtual void finish_graphviz();

	std::string output_file_path;
	Options options;

	Agraph_t *g;
	GVC_t *gvc;

private:
};
