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

bool ParseCommandLineWithProperties::parse_start(const std::string cmdline)
{
	string pattern = "^(\"([[:alnum:]]|[[:space:]])+\"|[[:alnum:]]+)[[:space:]]+.*";
	
	regex r(pattern);
	
	// 先判断是否匹配。
	if (!regex_match(cmdline, r)) {
		LOGE("Command line doesn't match pattern.\n");
		return false;
	}
	
	for(sregex_iterator it(cmdline.begin(), cmdline.end(), r), end_it; it != end_it; ++it) {
		const smatch &m = *it;
		for(auto s : m) {
			cout << s.str() + "@";
		}
		cout << endl;
		this->start = m[1].str();
	}
	
	return true;
}

bool ParseCommandLineWithProperties::parse_properties(const std::string cmdline)
{
	string pattern = "[[:space:]]+(\"([[:alnum:]]|[[:space:]])+\"|[[:alnum:]]+)=(\"([[:alnum:]]|[[:space:]])+\"|[[:alnum:]]+)(?=[[:space:]]*)";
	
	regex r(pattern);
		
	for(sregex_iterator it(cmdline.begin(), cmdline.end(), r), end_it; it != end_it; ++it) {
		const smatch &m = *it;
		for(auto s : m) {
			cout << s.str() + "@";
		}
		cout << endl;
		this->properties.push_back(make_pair(m[1].str(), m[3].str()));
	}
	
	return true;
}

bool ParseCommandLineWithProperties::parse(const std::string cmdline)
{
	this->start = "";
	this->properties.clear();
	
	if (!parse_start(cmdline)) {
		return false;
	}
	
	if (!parse_properties(cmdline)) {
		this->start = "";
		return false;
	}
	
	return true;
}