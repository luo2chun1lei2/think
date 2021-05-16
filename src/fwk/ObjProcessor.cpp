#include <fwk/ObjProcessor.hpp>

#include <ext/ObjValue.hpp>

#include <misc/Misc.hpp>

using namespace std;

ObjProcessorLine::ObjProcessorLine(const std::string name)
    : Object(name) {
}
ObjProcessorLine::~ObjProcessorLine() {
}

bool ObjProcessorLine::begin_notify() {
    return true;
}

bool ObjProcessorLine::notify(Object *obj) {
    return true;
}

// 注意下面的绘制：Object 和 Relation 都是Node，然后之间用节点相连。
bool ObjProcessorLine::end_notify() {
    return true;
}