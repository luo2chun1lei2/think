#pragma once

/**
 * @file
 * @brief 解析命令行
 */

#include <string>
#include <vector>

/**
 * @brief 解析后的Main需要执行的控制参数。
 * 
 */
struct MainControl
{
public:
    // 开始是否执行脚本。
    std::vector<std::string> script_pathes;
    // 执行脚本后，是否进入交互模式。
    bool enter_interactive;
    
    MainControl();
};

/**
 * @brief 解析命令行参数。
 * 
 * @param argc 
 * @param argv 
 * @return true 没有问题。
 * @return false 出现问题。
 */
bool parse_command_args(MainControl * control, int argc, char *argv[]);