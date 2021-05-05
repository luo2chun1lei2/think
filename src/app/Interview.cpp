#include <app/Interview.hpp>

#include <stdio.h>
#include <string.h>

#include <misc/Misc.hpp>

using namespace std;

void Interview::show_help(void) {
    LOGI("help/h: show help information.\n");
    LOGI("quit/q: quit from console.\n");
}

int Interview::do_inner_cmd(const char *line) {
    if (strcmp("quit", line) == 0 || strcmp("q", line) == 0) {
        return true;
    } else if (strcmp("help", line) == 0 || strcmp("h", line) == 0) {
        show_help();
    } else {
        LOGE("Unkown command: \"%s\"\n", line);
    }

    return false;
}

/**
 * parse the input line.
 * @return isquit ?
 */
int Interview::parse_input(const char *line) {
    // 所有以 “!" 开始的单词都是内部的命令。
    if (line[0] == '!') {
        return do_inner_cmd(line + 1);
    } else {
        process->exec(line);
    }
    return false;
}

void Interview::loop() {
    ProcessCmdLine process;
    bool is_quit = false;

    char *line;
    size_t line_n;
    while (getline(&line, &line_n, stdin) != -1) {
        size_t l = strlen(line);
        if ( line[l-1] == '\n' ) {
            line[l-1] = '\0';
        }
        is_quit = parse_input(line);

        free(line);
        line = NULL;
        line_n = 0;

        if (is_quit) {
            break;
        }
    }
}