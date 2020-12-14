// misc functions.
#pragma once

#include <stdio.h>

#include <string>
#include <vector>

#define LOGE(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#define LOGI(fmt, ...) fprintf(stdout, fmt, ##__VA_ARGS__)

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
	
	virtual std::string get_prop_value(const std::string prop_key);
	
protected:
	virtual bool parse_match(const std::string cmdline);
	virtual bool parse_start(const std::string cmdline);
	virtual bool parse_properties(const std::string cmdline);

	std::string start;
	Properties properties;
	
private:
};
