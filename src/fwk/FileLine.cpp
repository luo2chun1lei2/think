#include <FileLine.hpp>

#include <misc/Misc.hpp>

FileLine::FileLine(const std::string name)
    : Object(name) {
        _string = "";
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
    if (_path.empty()) {
        is_error = false;
        return "";
    }

    // TODO: 脚本的读取，需要单独抽取出来做成函数。
    FILE *fp = fopen(_path.c_str(), "r");
    if (!fp) {
        LOGE("Cannot open file(%s)\n", script_path);
        return false;
    }

    char *buf = NULL;
    size_t buf_size = 0;
    while (getline(&buf, &buf_size, fp) != -1) {
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

        free(buf);
        buf = NULL;
        buf_size = 0;
    }

    fclose(fp);
}