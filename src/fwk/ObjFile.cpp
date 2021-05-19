#include <fwk/ObjFile.hpp>

#include <misc/Misc.hpp>

using namespace std;

FileLine::FileLine(const std::string name)
    : Object(name) {
    _path = "";
    _fp = NULL;
}

FileLine::~FileLine() {
	if(_fp) {
	    fclose(_fp);
	}
}

bool FileLine::begin_notify() {
    // Do nothing
    return false;
}

bool FileLine::notify(Object *obj) {
    return false;
}

bool FileLine::end_notify() {
    return false;
}

void FileLine::set_path(const std::string path) {
    _path = path;
}

const std::string FileLine::get_line(int index, bool &is_end, bool &is_error) {
    is_end = false;
    is_error = false;

    if (_path.empty()) {
        is_end = true;
        return "";
    }

    if (_fp == NULL) {
        _fp = fopen(_path.c_str(), "r");
        if (!_fp) {
            LOGE("Cannot open file(%s)\n", _path.c_str());
            is_error = true;
            return "";
        }
    }

    char *buf = NULL;
    size_t buf_size = 0;
    if (getline(&buf, &buf_size, _fp) == -1) {
        is_end = true;
        return "";
    }

    string result = buf;
    free(buf);
    return result;
}
