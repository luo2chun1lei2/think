#include <fwk/FileLine.hpp>

#include <ext/ObjValue.hpp>

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

///////////////////////////////////////////////////////////
RltPipeLine::RltPipeLine(const std::string name)
    : Relation(name) {
}

RltPipeLine::~RltPipeLine() {
}

bool RltPipeLine::perform(std::vector<Object *> &need_objs) {
    // TODO: 怎么避免强制类型转换?
    FileLine *from = dynamic_cast<FileLine *>(this->objects[0]);
    Object *to = this->objects[1];

    to->begin_notify();

    bool is_error;
    bool is_end;
    do {
        is_error = false;
        is_end = false;
        string line = from->get_line(-1, is_end, is_error);

        ObjValue objLine("command");
        objLine.set_value(Value(line));
        to->notify(&objLine);

    } while (is_end == false);

    to->end_notify();
}

///////////////////////////////////////////////////////////
ObjProcessLine::ObjProcessLine(const std::string name)
    : Object(name) {
}
ObjProcessLine::~ObjProcessLine() {
}

bool ObjProcessLine::begin_notify() {
    return true;
}

bool ObjProcessLine::notify(Object *obj) {

    return true;
}

// 注意下面的绘制：Object 和 Relation 都是Node，然后之间用节点相连。
bool ObjProcessLine::end_notify() {
    return true;
}
