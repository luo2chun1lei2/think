#include <Misc.hpp>

#include <iostream>
#include <regex>

using namespace std;

bool CombineLine::add(std::string line, std::string &all)
{
	if (line.back() == '\\') {
		this->all.append(line.substr(0, line.size()-1));
		return false;
	} else {
		all=this->all.append(line);
		this->all.clear();
		return true;
	}
}

// TODO: 用正则表达式实现下面的逻辑分析，已经很难维护了。

// 命令行的格式： ElementType property_name=property_value property_name=property_value
// ElementType格式等于 property_name
// perperty_name : 是两种情况，一种是用双引号来括起来文字，什么文字都可以。另外一种是"汉字\字母\数\.\_"组成的无空格字符串。 //===========================> HERE
// 比如：  abc123  or   "a b c 1 2 3" or abc.123 or abc_123
// \u4e00-\u9fa5 是中文。
// 区分名字和值，是不同的表达式。
#define TAG "(\"([\u4e00-\u9fa5a-zA-Z0-9\\._]|[[:space:]])+\"|[\u4e00-\u9fa5a-zA-Z0-9\\._]+)"
#define TAG_VALUE "(\"([\u4e00-\u9fa5a-zA-Z0-9\\._]|[[:space:]])+\"|[\u4e00-\u9fa5a-zA-Z0-9\\._]+)"

bool ParseCommandLineWithProperties::parse_match(const std::string cmdline)
{
	string pattern = "^[[:space:]]*" TAG "([[:space:]]+" TAG "=" TAG ")*[[:space:]]*$";
	
	regex r(pattern);
	
	// 先判断是否匹配。
	if (regex_match(cmdline, r)) {
		return true;
	} else {
		LOGE("Command line doesn't match pattern.\n");
		return false;
	}
}

bool ParseCommandLineWithProperties::parse_start(const std::string cmdline)
{
	string pattern = "^(\"([\u4e00-\u9fa5a-zA-Z0-9\\._]|[[:space:]])+\"|[\u4e00-\u9fa5a-zA-Z0-9\\._]+)[[:space:]]*";
	
	regex r(pattern);
	
	for(sregex_iterator it(cmdline.begin(), cmdline.end(), r), end_it; it != end_it; ++it) {
		const smatch &m = *it;
//		for(auto s : m) {
//			cout << s.str() + "@";
//		}
//		cout << endl;
		this->start = m[1].str();
	}
	
	return true;
}

bool ParseCommandLineWithProperties::parse_properties(const std::string cmdline)
{
	string pattern = "[[:space:]]+(\"([\u4e00-\u9fa5a-zA-Z0-9\\._]|[[:space:]])+\"|[a-zA-Z0-9\\._]+)=(\"([\u4e00-\u9fa5a-zA-Z0-9\\._]|[[:space:]])+\"|[\u4e00-\u9fa5a-zA-Z0-9\\._]+)(?=[[:space:]]*)";
	
	regex r(pattern);
		
	for(sregex_iterator it(cmdline.begin(), cmdline.end(), r), end_it; it != end_it; ++it) {
		const smatch &m = *it;
//		for(auto s : m) {
//			cout << s.str() + "@";
//		}
//		cout << endl;
		this->properties.push_back(make_pair(m[1].str(), m[3].str()));
	}
	
	return true;
}

bool ParseCommandLineWithProperties::parse(const std::string cmdline)
{
	this->start = "";
	this->properties.clear();
	
	if (!parse_match(cmdline)) {
		return false;
	}
	
	if (!parse_start(cmdline)) {
		return false;
	}
	
	if (!parse_properties(cmdline)) {
		this->start = "";
		return false;
	}
	
	return true;
}

std::string ParseCommandLineWithProperties::get_prop_value(const std::string prop_key)
{
	for(pair<string, string> one : this->properties) {
		if (one.first == prop_key) {
			return one.second;
		}
	}
	
	return "";
}

///////////////////////////////////////////////////////////

// 表达式中的名字的特点。
#define EXPR_NAME "(\"([a-zA-Z0-9_]|[[:space:]])+\"|[a-zA-Z0-9_]+)"

bool ParseExpr::parse_match(const string input)
{
	// TAG.TAG.TAG ……
	string pattern = "^[[:space:]]*" EXPR_NAME "(\\." EXPR_NAME ")*[[:space:]]*$";
	
	regex r(pattern);
	
	// 先判断是否匹配。
	if (!regex_match(input, r)) {
		LOGE("Input doesn't match pattern.\n");
		return false;
	}

	return true;
}

bool ParseExpr::parse_tree(const string input)
{
	// 用分割的方式来分析语法。
	std::regex reg("\\.");
	std::sregex_token_iterator pos(input.begin(), input.end(), reg, -1);
	decltype(pos) end;
	for (; pos != end; ++pos)
	{
		//std::cout << pos->str() << std::endl;
		this->path.push_back(pos->str());
	}

	return true;
}


bool ParseExpr::parse(const std::string expr)
{
	this->path.clear();
	
	if (!parse_match(expr)) {
		return false;
	}
		
	if (!parse_tree(expr)) {
		return false;
	}
	
	return true;
}

ParseExpr::Path ParseExpr::get_path()
{
	return path;
}
