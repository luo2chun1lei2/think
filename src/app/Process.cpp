#include <Process.hpp>

#include <stdlib.h>
#include <unistd.h>

#include <Misc.hpp>
#include <Output.hpp>
#include <Query.hpp>

#include <sstream>

using namespace std;

/// 执行 一个脚本文件，直到文件结束。
bool exec_script(const char *script_path) {
    ProcessCmdLine process;

    if (script_path) {
        // TODO: 脚本的读取，需要单独抽取出来做成函数。
        FILE *fp = fopen(script_path, "r");
        if (!fp) {
            LOGE("Cannot open file(%s)\n", script_path);
            return 1;
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

    return true;
}

bool ProcessCmdLine::output_graphviz(const string name, ParseCommandLineWithProperties &parse) {

    string str_option = parse.get_prop_value("option");
    string str_type = parse.get_prop_value("type");

    OutputGraphviz *output = nullptr;

    OutputGraphviz::Type type;
    if (str_type == "basic") {
        type = OutputGraphviz::TYPE_BASIC;
    } else if (str_type == "list") {
        type = OutputGraphviz::TYPE_LIST;
    } else if (str_type == "call") {
        type = OutputGraphviz::TYPE_CALL;
    } else if (str_type == "layout") {
        type = OutputGraphviz::TYPE_LAYOUT;
    } else {
        type = OutputGraphviz::TYPE_BASIC;
    }

    if (str_option == "text") {
        output = new OutputGraphviz(name, OutputGraphviz::GRAPH_TEXT, type);

        // 生成临时文件。
        char path[] = "/tmp/XXXXXX.txt";
        int fd = mkstemps(path, 4);
        if (fd == -1) {
            LOGE("Cannot open temp file.\n");
            return false;
        }
        close(fd);

        // 设定临时文件路径。
        output->set_output_filepath(path);
        output->output(this->model);

        // 显示graphviz内部的绘制脚本，而不是dot本身的脚本。
        ostringstream stream;
        stream << "cat " << path;
        auto cmd = stream.str();
        system(cmd.c_str());
    } else { // SVG is default。
        output = new OutputGraphviz(name, OutputGraphviz::GRAPH_SVG, type);

        // 生成临时文件。
        char path[] = "/tmp/XXXXXX.svg";
        int fd = mkstemps(path, 4);
        if (fd == -1) {
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
    }

    return true;
}

bool ProcessCmdLine::init_all_properties(Element *elm, ParseCommandLineWithProperties::Properties properties) {

    for (pair<string, string> one : properties) {
        if (one.first == "name") {
            continue;
        }

        model->set_property_of_elm(elm, one.first, one.second);
    }

    return true;
}

// TODO: 函数过大了，应该拆分。
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
        // Create a model
        Model *model = new Model(name);
        this->set_model(model);
        return true;
    } else if (start_str == "Output") {
        // output model.
        return output_graphviz(name, parse);

    } else if (start_str == "Element") {
        // Create a element.
        Element *elm = new Element(name);

        model->add_elm(elm);

        if (!init_all_properties(elm, properties)) {
            LOGE("Cannot initialize properties of element(%s).\n", name.c_str());
            return false;
        }

        return true;

    } else if (start_str == "Relation") {
        // Create a relation.
        Relation *rlt = new Relation(name);

        if (!init_all_properties(rlt, properties)) {
            LOGE("Cannot initialize properties of relation(%s).\n", name.c_str());
            return false;
        }

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
    }

    LOGE("Unknown(%s) element or operation.\n", start_str.c_str());
    return false;
}
