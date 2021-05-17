/**
 * 使用Graphviz绘制一个图片。
 */
#pragma once

#include <string>
#include <graphviz/gvc.h>

/**
 * 显示一个 Graphviz 图形。
 */
class Graphviz
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

    // 初始化一个Graphviz对象。
	Graphviz(const std::string name, Graphviz::Option option, Graphviz::Type type);
	virtual ~Graphviz();
    // 需要设定导出的文件路径。
	virtual void set_output_filepath(const std::string path);
	virtual std::string get_output_filepath();
    // 将一个模型导出！
	//virtual bool output(const Model *model);

    // 绘制之前准备。
	virtual bool prepare_graphviz();
    // 绘制后清理资源。
	virtual void finish_graphviz();

    virtual Agnode_t * add_node(const std::string str, bool is_node);

    virtual Agedge_t * add_edge(const std::string str, Agnode_t *f, Agnode_t *t);

protected:

	std::string output_file_path;
	Option option;
	Type type;

	Agraph_t *g;
	GVC_t *gvc;

private:
};