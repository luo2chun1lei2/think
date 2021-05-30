#include "ObjInterview.hpp"

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <misc/Misc.hpp>

using namespace std;

ObjInterview::ObjInterview(const std::string name) : Object(name) {
}

ObjInterview::~ObjInterview() {
}

bool ObjInterview::begin_notify() {
    // Do nothing
    return false;
}

bool ObjInterview::notify(Object *obj) {
    return false;
}

bool ObjInterview::end_notify() {
    return false;
}

const std::string ObjInterview::get_line(int index, bool &is_end, bool &is_error) {
    is_end = false;
    is_error = false;

    // get string from std in.
    char *line = NULL;
    size_t line_n = 0;

    if (getline(&line, &line_n, stdin) == -1) {
    	// 遇到错误或者文件尾部，getline会返回 -1.
    	if (!errno) {
		is_error = true;
    		return "";
    	} else {
    		is_end = true;
    		return "";
    	}
    }

    size_t l = strlen(line);
    if (line[l - 1] == '\n') {
        line[l - 1] = '\0';
    }

    string result = line;

    free(line);
    return result;
}

#if 0
void ObjInterview::show_help(void) {
    LOGI("help/h: show help information.\n");
    LOGI("quit/q: quit from console.\n");
}

int ObjInterview::do_inner_cmd(const char *line) {
    if (strcmp("quit", line) == 0 || strcmp("q", line) == 0) {
        return true;
    } else if (strcmp("help", line) == 0 || strcmp("h", line) == 0) {
        show_help();
    } else {
        LOGE("Unknown command: \"%s\"\n", line);
    }

    return false;
}

/**
 * parse the input line.
 * @return is quit ?
 */
int ObjInterview::parse_input(const char *line) {
    // 所有以 “!" 开始的单词都是内部的命令。
    if (line[0] == '!') {
        return do_inner_cmd(line + 1);
    } else {
        process->exec(line);
    }
    return false;
}
#endif
