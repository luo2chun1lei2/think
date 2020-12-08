#pragma once

#include <string>

#include <Model.hpp>

/**
 * 将Model导出
 * TODO: 后面也做成Element。
 */
class Output
{
public:
	Output() {}
	virtual ~Output() {}
	virtual bool output(const Model &model) = 0;
protected:
private:
};

/**
 * 将Model导出到Graphviz
 */
class OutputGraphviz : public Output
{
public:
	OutputGraphviz();
	virtual ~OutputGraphviz();
	virtual void set_output_filepath(const std::string path);
	virtual bool output(const Model &model);
protected:
	std::string output_file_path;
private:
};
