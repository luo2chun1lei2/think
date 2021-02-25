#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include <Misc.hpp>

#include <Process.hpp>

static const char *_sopts = "hi";
extern char *optarg;
static const struct option _lopts[] = {
    {"help", no_argument, 0, 'h'}, {"interactive", no_argument, 0, 'i'}, {0, 0, 0, 0}};

static const char *usage = "Usage: %s [options] <script path>\n"
                           "  <script path>   execute script by given path.\n"
                           "options:\n"
                           "  -h, --help            prints this message and exit.\n"
                           "  -i, --interactive     run into interactive mode.\n"
                           "\n";

static void print_usage_and_exit(const char *prog, int code) {
    LOGE(usage, prog);
    exit(code);
}

// TODO 为了测试方便，需要将main中的方法都放到其他的文件中。
int main(int argc, char *argv[]) {
    // LOGI("start think...\n");

    int c;
    int oidx = 0;

    bool enter_interactive = true;
    const char *script_path = NULL;

    while (1) {
        c = getopt_long(argc, argv, _sopts, _lopts, &oidx);
        if (c == -1)
            break; /* done */

        switch (c) {
            case 'h':
                print_usage_and_exit(argv[0], EXIT_SUCCESS);
                break;
            case 'i':
                enter_interactive = true;
                break;
            default:
                print_usage_and_exit(argv[0], EXIT_FAILURE);
                break;
        }
    }

    // 非option的参数，就是脚本的路径。
    // TODO 目前只支持一个，且最后一个。
    if (optind < argc) {
        while (optind < argc)
            script_path = argv[optind++];
    }

    ProcessCmdLine process;

    if (script_path) {
        // TODO: 脚本的读取，需要单独抽取出来做成函数。
        FILE *fp = fopen(script_path, "r");
        if (!fp) {
            LOGE("Cannot open file(%s)\n", script_path);
            return 1;
        }
        char buf[1024]; // TODO: 假定一行最大是1024字节。
        while (fgets(buf, sizeof(buf), fp)) {
            // LOGI("read line:%s\n", buf);
            if (buf[0] == '#') {
                // TODO: 注释忽略，但是算法过于简单。
                continue;
            }

            // TODO: 排除空行，这个实现逻辑也不准确。
            if (buf[0] == '\n') { // 仅仅有一个'\n'
                continue;
            }
            process.exec(buf);
        }
        fclose(fp);
    }

    if (enter_interactive) {
        // TODO: 交互模式。目前没有需要，所以先不实现。
    }

    return 0;
}
