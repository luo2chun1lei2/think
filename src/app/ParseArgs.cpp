#include <app/ParseArgs.hpp>

#include <getopt.h>

#include <misc/Misc.hpp>

using namespace std;

MainControl::MainControl() {
    enter_interactive = false;
}

static const char *_sopts = "hi";

static const struct option _lopts[] = {
    {"help", no_argument, 0, 'h'}, {"interactive", no_argument, 0, 'i'}, {0, 0, 0, 0}};

static const char *usage = "Usage: %s [options] [script path ...]\n"
                           "  [script path]   execute script by given path, can be multiple string split by space.\n"
                           "options:\n"
                           "  -h, --help            prints this message and exit.\n"
                           "  -i, --interactive     run into interactive mode.\n"
                           "\n";

static void print_usage_and_exit(const char *prog, int code) {
    LOGE(usage, prog);
    exit(code);
}

bool parse_command_args(MainControl *control, int argc, char *argv[]) {
    extern char *optarg;

    int c;
    int oidx = 0;

    while (1) {
        c = getopt_long(argc, argv, _sopts, _lopts, &oidx);
        if (c == -1)
            break; /* done */

        switch (c) {
            case 'h':
                print_usage_and_exit(argv[0], EXIT_SUCCESS);
                break;
            case 'i':
                control->enter_interactive = true;
                break;
            default:
                print_usage_and_exit(argv[0], EXIT_FAILURE);
                return false;
        }
    }

    // 非option的参数，就是脚本的路径。
    // TODO 目前只支持一个，且最后一个。
    if (optind < argc) {
        while (optind < argc) {
            control->script_pathes.push_back(string(argv[optind]));
            optind++;
        }
    }

    return true;
}