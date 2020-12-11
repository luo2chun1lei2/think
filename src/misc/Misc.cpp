#include <Misc.hpp>

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

bool ParseCommandLineWithProperties::parse(const std::string cmdline)
{
	return false;
}