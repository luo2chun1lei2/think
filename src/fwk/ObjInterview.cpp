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
