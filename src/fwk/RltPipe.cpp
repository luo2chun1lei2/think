#include <fwk/RltPipe.hpp>

#include <ext/ObjValue.hpp>

#include <misc/Misc.hpp>

using namespace std;

RltPipeLine::RltPipeLine(const std::string name) :
		Relation(name) {
}

RltPipeLine::~RltPipeLine() {
}

bool RltPipeLine::perform(std::vector<Object*> &need_objs) {

	for (Object *obj : _from_objs) {
		// TODO: 怎么避免强制类型转换?
		if (!exec_one_obj(dynamic_cast<ILine*>(obj))) {
			return false;
		}
	}
	return true;
}

bool RltPipeLine::exec_one_obj(ILine *pline) {

	for (Object *to : _to_objs) {
		to->begin_notify();
	}

	bool is_error;
	bool is_end;
	do {
		is_error = false;
		is_end = false;
		string line = pline->get_line(-1, is_end, is_error);

		exec_one_line(line);
		if (is_end) {
			LOGD("meet end of input.\n");
		}

		if (is_error) {
			LOGD("meet error of input.\n");
		}

	} while (is_end == false && is_error == false);

	for (Object *to : _to_objs) {
		to->end_notify();
	}

	return true;
}

bool RltPipeLine::exec_one_line(std::string str_line) {
	ObjValue objLine("command");
	objLine.set_value(Value(str_line));
	for (Object *to : _to_objs) {
		to->notify(&objLine);
	}
	return true;
}

