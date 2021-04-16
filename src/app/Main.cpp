#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include <misc/Misc.hpp>

/*
#include <Interview.hpp>
#include <Process.hpp>
*/

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

int main(int argc, char *argv[]) {
    // LOGI("start think...\n");

    int c;
    int oidx = 0;

    bool enter_interactive = false;
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

    /*
        exec_script(script_path);

        if (enter_interactive) {
            Interview interview;
            interview.loop();
        }
    */
    return 0;
}
