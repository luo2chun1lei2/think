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
    ObjValue *objValue = dynamic_cast<ObjValue *>(obj);

    Value v = objValue->get_value();
    if (v.get_type() != v.TYPE_STR) {
        LOGE("Input value is string, is %d.\n", v.get_type());
        return false;
    }
    LOGI("==>%s\n", v.get_str().c_str());

    return true;
}

bool ObjProcessorLine::end_notify() {
    return true;
}