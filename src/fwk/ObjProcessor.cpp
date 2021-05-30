#include <fwk/ObjProcessor.hpp>

#include <misc/Misc.hpp>

#include <ext/ObjValue.hpp>

#include <fwk/ObjGraphviz.hpp>

using namespace std;

ObjProcessorLine::ObjProcessorLine(const std::string name) :
		Object(name) {
	_model = nullptr;

	set_property("is_quit", "", false);
}

ObjProcessorLine::ObjProcessorLine(const std::string name, Model *model) :
		Object(name) {
	this->_model = model;

	set_property("is_quit", "", false);
}

ObjProcessorLine::~ObjProcessorLine() {
	if (_model) {
		delete _model;
	}
}

void ObjProcessorLine::set_model(Model *model) {
	if (this->_model)
		delete this->_model;
	this->_model = model;
}

bool ObjProcessorLine::begin_notify() {
	return true;
}

bool ObjProcessorLine::notify(Object *obj) {
	ObjValue *objValue = dynamic_cast<ObjValue*>(obj);

	Value v = objValue->get_value();
	if (v.get_type() != v.TYPE_STR) {
		LOGE("Input value is string, is %d.\n", v.get_type());
		return false;
	}
	//LOGI("==>%s\n", v.get_str().c_str());
	exec(v.get_str());

	return true;
}

bool ObjProcessorLine::end_notify() {
	return true;
}

void ObjProcessorLine::show_help(void) {
	LOGI("help/h: show help information.\n");
	LOGI("quit/q: quit from console.\n");
}

void ObjProcessorLine::quit(void) {
	// TODO: 如何从程序退出！
	set_property("is_quit", "", true);
}

bool ObjProcessorLine::do_inner_cmd(const std::string line) {
	// TODO: 系统命令实际上应该交给更高级的来处理，而不是在这里处理。
	if ("quit" == line || "q" == line) {
		quit();
	} else if ("help" == line || "h" == line) {
		show_help();
	} else {
		LOGE("Unknown inner command: \"%s\"\n", line);
	}

	return true;
}

bool ObjProcessorLine::parse_inner_cmd(const std::string line) {
	// 所有以 “!" 开始的单词都是内部的命令。
	if (line[0] == '!') {
		return do_inner_cmd(line.substr(1));
	}

	return false;
}

// TODO: 函数过大了，应该拆分。
bool ObjProcessorLine::exec(const std::string cmd) {

	if (cmd[0] == '#') {
		// TODO: 注释忽略，但是算法过于简单。
		return true;
	}

	// TODO: 排除空行，这个实现逻辑也不准确。
	if (cmd[0] == '\n' || cmd.length() == 0) { // 仅仅有一个'\n'
		return true;
	}

	if (parse_inner_cmd(cmd)) {
		return true;
	}

	ParseCommandLineWithProperties parse;

	if (!parse.parse(cmd)) {
		return false;
	}

	string start_str = parse.get_start();
	// TODO: properties好像没有用？
	ParseCommandLineWithProperties::Properties properties =
			parse.get_properties();

	string name = parse.get_prop_value("name");
	if (name.empty()) {
		LOGE("At least set name of object.\n");
		return false;
	}

	// ParseCommandLineWithProperties::Properties properties = parse.get_all_properties_except_name();

	if (start_str == "Model") {
		// Create a model
		Model *model = new Model(name);
		this->set_model(model);
		return true;

	} else if (start_str == "Output") {
		// output model.
		// TODO: 这里当做动作！
		return output_graphviz(name, parse);

	} else if (start_str == "Object") {

		_model->add_obj(name, Properties());

		if (!init_all_properties(name, properties)) {
			LOGE("Cannot initialize properties of element(%s).\n", name.c_str());
			return false;
		}

		return true;

	} else if (start_str == "Relation") {
		// Create a relation.
		// Relation *rlt = new Relation(name);
		if (!_model->add_rlt(name, Properties())) {
			LOGE("Cannot add relation(%s).\n", name.c_str());
			return false;
		}

		if (!init_all_properties(name, properties)) {
			LOGE("Cannot initialize properties of relation(%s).\n",
					name.c_str());
			return false;
		}

		// get relate
		string relate_from_str = parse.get_prop_value("relate_from");
		if (relate_from_str == "") {
			LOGE("Relation(%s) doesn't set relation.\n",
					relate_from_str.c_str());
			return false;
		}

		vector<string> obj_from_names = split_str(relate_from_str, ",");

		for (string o : obj_from_names) {
			if (!_model->have_obj_by_name(o)) {
				LOGE("Relation(%s) cannot find related object(%s).\n",
						name.c_str(), o.c_str());
				return false;
			}
		}

		string relate_to_str = parse.get_prop_value("relate_to");
		if (relate_to_str == "") {
			LOGE("Relation(%s) doesn't set relation.\n", relate_to_str.c_str());
			return false;
		}

		vector<string> obj_to_names = split_str(relate_to_str, ",");

		for (string o : obj_to_names) {
			if (!_model->have_obj_by_name(o)) {
				LOGE("Relation(%s) cannot find related object(%s).\n",
						name.c_str(), o.c_str());
				return false;
			}
		}

		// set relation between objects and relation.
		//printf("%s->%s\n", obj_from_names[0].c_str(), obj_to_names[0].c_str());
		_model->relate(name, obj_from_names, obj_to_names);

		return true;
		/*
		 } else if (start_str == "Query") {
		 // TODO: 生成一个查询对象，应该是临时的？或者是永久的？
		 Query *query = new Query(name);

		 string expr = parse.get_prop_value("value");

		 Element *elm = query->query(model, expr);
		 // TODO: 这里用日志直接输出，有点不好吧？

		 string result = "error";
		 if (elm) {
		 result = elm->get_value();
		 }
		 LOGI("%s\n", result.c_str());
		 return true;
		 } else if (start_str == "Clear") {
		 // TODO: no impl，感觉没有必要！
		 return false;
		 */
	}

	LOGE("Unknown(%s) element or operation.\n", start_str.c_str());

	return false;
}

bool ObjProcessorLine::output_graphviz(const string name,
		ParseCommandLineWithProperties &parse) {

	string str_option = parse.get_prop_value("option");
	string str_type = parse.get_prop_value("type");

	Graphviz::Type type;
	if (str_type == "basic") {
		type = Graphviz::TYPE_BASIC;
	} else if (str_type == "list") {
		type = Graphviz::TYPE_LIST;
	} else if (str_type == "call") {
		type = Graphviz::TYPE_CALL;
	} else if (str_type == "layout") {
		type = Graphviz::TYPE_LAYOUT;
	} else {
		type = Graphviz::TYPE_BASIC;
	}

	if (str_option == "text") {
		ObjGraphviz graphviz("output");
		graphviz.begin_notify();
		for (Object *obj : this->_model->get_objs()) {
			graphviz.notify(obj);
		}
		graphviz.end_notify();

	} else { // SVG is default。
		ObjGraphviz graphviz("output");
		graphviz.begin_notify();
		for (Object *obj : this->_model->get_objs()) {
			graphviz.notify(obj);
		}
		graphviz.end_notify();
	}

	return true;
}

bool ObjProcessorLine::init_all_properties(string obj_name,
		ParseCommandLineWithProperties::Properties properties) {

	for (pair<string, string> one : properties) {
		if (one.first == "name") {
			continue;
		}

		if (one.first == "relate_from" || one.first == "relate_to") {
			continue;
		}

		_model->add_prop_of_obj(obj_name, one.first, one.second);
	}

	return true;
}
