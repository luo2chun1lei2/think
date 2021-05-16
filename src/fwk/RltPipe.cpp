#include <fwk/RltPipe.hpp>

#include <ext/ObjValue.hpp>
#include <fwk/ObjFile.hpp>

#include <misc/Misc.hpp>

using namespace std;

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
