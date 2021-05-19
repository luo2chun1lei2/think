#pragma once

// 接口，一行一行的读取数据。
class ILine
{
public:
	virtual const std::string get_line(int index, bool &is_end, bool &is_error) = 0;
};