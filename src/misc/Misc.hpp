// misc functions.
#pragma once

#include <stdio.h>

#include <string>
#include <vector>

#define LOGE(fmt, ...) {fprintf(stderr, "E:%s:%d ", __FILE__, __LINE__); fprintf(stderr, fmt, ##__VA_ARGS__);}
#define LOGW(fmt, ...) {fprintf(stdout, "W:%s:%d ", __FILE__, __LINE__); fprintf(stdout, fmt, ##__VA_ARGS__);}
#define LOGI(fmt, ...) {fprintf(stdout, "I:%s:%d ", __FILE__, __LINE__); fprintf(stdout, fmt, ##__VA_ARGS__);}
#define LOGD(fmt, ...) {fprintf(stdout, "D:%s:%d ", __FILE__, __LINE__); fprintf(stdout, fmt, ##__VA_ARGS__);}

/**
 * 在脚本或者命令行时，会出现多行写一个命令的时候，未完成的行后面用”\“来标记，
 * 这个工具类就是根据”\“将多行合并成一行。
 */
class CombineLine
{
public:
	CombineLine() : all("") {}

	// 添加一行，如果行后面有“\n"，那么就会返回false，并且将此行合并到内部的行。
	// 否则返回true，all就是内部行文字，然后内部行清空。
	virtual bool add(std::string line, std::string &all);

protected:
	std::string all;
};

/**
 * 分析一行属性命令，然后将命令分解成对应的属性。
 * format:
 * start prop_name=prop_value prog_name=prop_value ...
 * prop_name 和 prop_value 可以用双引号扩上，这样就可以有空格。
 * 例子：
 * Relation name="父子“ from="罗父“ to=”罗某“
 * 注意分析后的属性等，如果原来带有双引号，那么解析后也会带有双引号。
 */
class ParseCommandLineWithProperties
{
public:
	using Properties = std::vector<std::pair<std::string, std::string>>;

	ParseCommandLineWithProperties() {}
	virtual ~ParseCommandLineWithProperties() {}
	
	// 如果命令不和要求，就返回false，其他返回true，properties里面是键值对。
	// 因为这里不考虑key的重复问题，所以用vector。
	virtual bool parse(const std::string cmdline);
	
	virtual std::string get_start() {
		return start;
	}
	
	virtual Properties get_properties() {
		return properties;
	}

	virtual Properties get_all_properties_except_name() {
		Properties no_names;
		for(auto one : properties) {
			if (one.first != "name") {
				no_names.push_back(one);
			}
		}
		return no_names;
	}
	
	virtual std::string get_prop_value(const std::string prop_key);
	
protected:
	virtual bool parse_match(const std::string cmdline);
	virtual bool parse_start(const std::string cmdline);
	virtual bool parse_properties(const std::string cmdline);

	std::string start;
	Properties properties;
	
private:
};

/**
 * 分析表达式(不需要名字？)
 * 此处应该按照算数表达式来解析，然后其中的变量按照 Path 来解析。
 * 关系： xxx.xxx 由对象开始，沿着关系查找。
 * TODO: 逻辑： xxx == xxx
 * TODO: 算数表达式： xxx + xxx
 * 
 */
class ParseExpr
{
public:
// 路径，在
using Path = std::vector<std::string>;

	ParseExpr() {}
	virtual ~ParseExpr() {}
	
	// 如果命令不和要求，就返回false，其他返回true
	virtual bool parse(const std::string expr);

	virtual Path get_path();

protected:
	Path path;

	virtual bool parse_match(const std::string input);
	virtual bool parse_tree(const std::string input);

private:
};

std::vector<std::string> split_str(const std::string str, const std::string &delimiters = " ");

