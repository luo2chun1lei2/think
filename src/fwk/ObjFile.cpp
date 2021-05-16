#include <fwk/ObjFile.hpp>

#include <misc/Misc.hpp>

using namespace std;

FileLine::FileLine(const std::string name)
    : Object(name) {
    _path = "";
    _fp = NULL;
}

FileLine::~FileLine() {
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

    /* TODO: 需要过滤。
    // LOGI("read line:%s\n", buf);
    if (buf[0] == '#') {
        // TODO: 注释忽略，但是算法过于简单。
        continue;
    }

    // TODO: 排除空行，这个实现逻辑也不准确。
    if (buf[0] == '\n') { // 仅仅有一个'\n'
        continue;
    }
    */

    // TODO: return;
    string result = buf;
    free(buf);
    return result;

    // TODO: 没有fclose
    // fclose(fp);
}
