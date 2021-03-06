#include <stdio.h>
#include <stdlib.h>

#include <app/ParseArgs.hpp>

#include <fwk/ObjInterview.hpp>
#include <fwk/ObjFile.hpp>
#include <fwk/ObjProcessor.hpp>
#include <fwk/RltPipe.hpp>

#include <misc/Misc.hpp>

#include <vector>

using namespace std;

int main(int argc, char *argv[]) {

	// TODO: 这个Control并没有真正的控制程序!
    MainControl control;
    if (!parse_command_args(&control, argc, argv)) {
        exit(1);
    }

    /**
     * TODO:目前的设计: 我想通过脚本，生成不同的 Process（负责不同的脚本解析），
     * 但是想要设定不同的Process，那么就需要分析脚本的设定，这个就有矛盾，因为Process就是分析脚本的。
     * 全部由Process解析，但是Process可以组合。
     * 左边的负责，读取文件和通过交互的输入，中间的负责解析传入的数据，右边的负责管理OR-Net。
     * Script File  -- pipe --> Process         -- pipe --> DM
     *              -- pipe --> Special Process -- pipe --> DM
     * Interview    -- pipe -->
     */

    std::vector<Object *> files;
    for (string script_path : control.script_pathes) {
        FileLine *pfile = new FileLine("File");
        pfile->set_path(script_path);
        files.push_back(pfile);
    }
    files.push_back(new ObjInterview("interview"));

    std::vector<Object *> processes;

    ObjProcessorLine process("process");
    processes.push_back(&process);

    RltPipeLine pipe("pipe");
    pipe.relate(files, processes);

    std::vector<Object *> need_objs;
    pipe.perform(need_objs);

    return 0;
}
