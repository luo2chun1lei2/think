#pragma once

//#include <app/Process.hpp>

#if 0
/**
 * 交互界面。
 * 进入界面后，可以将输入的一行文字，发出去。
 */
class Interview
{
public:
    Interview(ProcessCmdLine * process) {
        this->process = process;
    }
    virtual ~Interview() {}

    // 进入循环，等待用户的输入和去处理。
    virtual void loop();

protected:
    virtual int parse_input(const char *line);
    virtual void show_help(void);
    virtual int do_inner_cmd(const char *line);
private:
    ProcessCmdLine * process;

};

#endif