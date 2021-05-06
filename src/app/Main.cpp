#include <stdio.h>
#include <stdlib.h>

#include <app/Interview.hpp>
#include <app/ParseArgs.hpp>
#include <app/Process.hpp>

#include <misc/Misc.hpp>

using namespace std;

int main(int argc, char *argv[]) {
    // LOGI("start think...\n");

    MainControl control;
    if (!parse_command_args(&control, argc, argv)) {
        exit(1);
    }

    /**
     * 目前的设计: 我想通过脚本，生成不同的 Process（负责不同的脚本解析），
     * 但是想要设定不同的Process，那么就需要分析脚本的设定，这个就有矛盾，因为Process就是分析脚本的。
     * 全部由Process解析，但是Process可以组合。
     * 左边的负责，读取文件和通过交互的输入，中间的负责解析传入的数据，右边的负责管理OR-Net。
     * Script File  -- pipe --> Process         -- pipe --> DM
     *              -- pipe --> Special Process -- pipe --> DM
     * Interview    -- pipe -->
     */

    ProcessCmdLine process;

    // TODO: Script files -> Process
    for (string script_path : control.script_pathes) {
        process.exec_script(script_path);
    }

    // TODO: Interview -> Process
    if (control.enter_interactive) {
        Interview interview(&process);
        interview.loop();
    }
    return 0;
}
