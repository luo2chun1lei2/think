#include <Process.hpp>

#include <stdlib.h>
#include <unistd.h>

#include <Misc.hpp>
#include <Output.hpp>
#include <Query.hpp>

#include <sstream>

using namespace std;

bool ProcessCmdLine::exec(const std::string cmd) {
	ParseCommandLineWithProperties parse;
	
	if (!parse.parse(cmd)) {
		return false;
	}
	
	string start_str = parse.get_start();
	// TODO: properties好像没有用？
	ParseCommandLineWithProperties::Properties properties = parse.get_properties();
	
	string name = parse.get_prop_value("name");
	if (name.empty()) {
		LOGE("At least set name of object.\n");
		return false;
	}
	
	if (start_str == "Model") {
		Model *model = new Model(name);
		this->set_model(model);
		return true;
	} else if(start_str == "Output") {
		OutputGraphviz * output = new OutputGraphviz(name);

		// 生成临时文件。
		char path[] = "/tmp/XXXXXX.svg";
        int fd = mkstemps(path, 4);
        if(fd == -1) {
			LOGE("Cannot open temp file.\n");
			return false;
		}
        close(fd);

		// 设定临时文件路径。
        output->set_output_filepath(path);
        output->output(this->model);

        // 执行显示图片的命令，system必须退出才行。
        ostringstream stream;
        stream << "eog " << path;
        auto cmd = stream.str();
        system(cmd.c_str());

		return true;
	} else if(start_str == "Output2") {
		OutputGraphviz * output = new OutputGraphviz(name);

		// 生成临时文件。
		char path[] = "/tmp/XXXXXX.txt";
        int fd = mkstemps(path, 4);
        if(fd == -1) {
			LOGE("Cannot open temp file.\n");
			return false;
		}
        close(fd);

		// 设定临时文件路径。
        output->set_output_filepath(path);
        output->output2(this->model);

        // 执行显示图片的命令，system必须退出才行。
        ostringstream stream;
        stream << "cat " << path;
        auto cmd = stream.str();
        system(cmd.c_str());

		return true;
	} else if(start_str == "Element") {
		Element *elm = new Element(name);
		model->add_elm(elm);
		return true;
	} else if(start_str == "Relation") {
		Relation *rlt = new Relation(name);

		string from_str = parse.get_prop_value("from");
		if (from_str == "") {
			LOGE("Relation(%s) hasn't from.\n", name.c_str());
			return false;
		}

		vector<Element *> from_elms = model->find_elm(from_str);
		if (from_elms.size() == 0) {
			LOGE("Relation(%s) cannot find from(%s).\n", name.c_str(), from_str.c_str());
			return false;
		}

		if (from_elms.size() > 1) {
			LOGE("Relation(%s) finds multiple from(%s).\n", name.c_str(), from_str.c_str());
			return false;
		}

		string to_str = parse.get_prop_value("to");
		if (to_str == "") {
			LOGE("Relation(%s) hasn't to.\n", name.c_str());
			return false;
		}

		vector<Element *> to_elms = model->find_elm(to_str);
		if (to_elms.size() == 0) {
			LOGE("Relation(%s) cannot find to(%s).\n", name.c_str(), to_str.c_str());
			return false;
		}

		if (to_elms.size() > 1) {
			LOGE("Relation(%s) finds multiple to(%s).\n", name.c_str(), to_str.c_str());
			return false;
		}

		rlt->relate(from_elms[0], to_elms[0]);

		model->add_elm(rlt);
		return true;

	} else if(start_str == "Query") {
		// TODO: 生成一个查询对象，应该是临时的？或者是永久的？
		Query * query = new Query(name);

		string expr = parse.get_prop_value("value");

		string result = query->query(model, expr);
		// TODO: 这里用日志直接输出，有点不好吧？
		LOGI("value=%s\n", result.c_str());
		return true;
	} else if(start_str == "Clear") {
		// TODO: no impl
		return false;
	}
	
	LOGE("Unknown(%s) element or operation.\n", start_str.c_str());
	return false;	
}
