#pragma once

#include <core/Object.hpp>
#include <fwk/ILine.hpp>

/**
 * 交互界面。
 * 进入界面后，可以将输入的一行文字，发出去。
 */
class ObjInterview : public Object, public ILine
{
public:
    ObjInterview(const std::string name);
    virtual ~ObjInterview();

    ///////////////////////////////////////////////////////
	// 根据通知，同步

	// 通知开始
	virtual bool begin_notify();
	// 通知都有哪些对象。
	virtual bool notify(Object *obj);
	// 通知结束，绘制并显示结果。
	virtual bool end_notify();

	///////////////////////////////////////////////////////
	// 获取数据

	/**
	 * 读取文件的一行数据。
	 * 1. 文件读取失败。
	 * 2. 超出文件结尾。
	 * 3. 正常结果。
	 * @param index -1: 继续下一个
	 */
	virtual const std::string get_line(int index, bool &is_end, bool &is_error);

protected:
#if 0
    virtual int parse_input(const char *line);
    virtual void show_help(void);
    virtual int do_inner_cmd(const char *line);
    // 进入循环，等待用户的输入和去处理。
    virtual void loop();
#endif
private:

};
