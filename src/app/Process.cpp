#include <app/Process.hpp>
#include <misc/Graphviz.hpp>
#include <fwk/ObjGraphviz.hpp>

#include <stdlib.h>
#include <unistd.h>

#include <sstream>

using namespace std;

/**
 * 执行 一个脚本文件，直到文件结束。
 */
bool ProcessCmdLine::exec_script(std::string script_path) {
    ProcessCmdLine process;
    if (script_path.empty()) {
        // 什么都不用执行，就当做正常结束。
        return true;
    }

    // TODO: 脚本的读取，需要单独抽取出来做成函数。
    FILE *fp = fopen(script_path.c_str(), "r");
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

        model->add_obj(name, Properties());

        if (!init_all_properties(name, properties)) {
            LOGE("Cannot initialize properties of element(%s).\n", name.c_str());
            return false;
        }

        return true;

    } else if (start_str == "Relation") {
        // Create a relation.
        // Relation *rlt = new Relation(name);
        if (!model->add_rlt(name, Properties())) {
            LOGE("Cannot add relation(%s).\n", name.c_str());
            return false;
        }

        if (!init_all_properties(name, properties)) {
            LOGE("Cannot initialize properties of relation(%s).\n", name.c_str());
            return false;
        }

        // get relate
        string relate_str = parse.get_prop_value("relate");
        if (relate_str == "") {
            LOGE("Relation(%s) doesn't set relation.\n", relate_str.c_str());
            return false;
        }

        vector<string> obj_names = split_str(relate_str, ",");

        for (string o : obj_names) {
            if (!model->have_obj_by_name(o)) {
                LOGE("Relation(%s) cannot find related object(%s).\n", name.c_str(), o.c_str());
                return false;
            }
        }

        // set relation between objects and relation.
        model->relate(name, obj_names);

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

bool ProcessCmdLine::output_graphviz(const string name, ParseCommandLineWithProperties &parse) {

    string str_option = parse.get_prop_value("option");
    string str_type = parse.get_prop_value("type");

    Graphviz *output = nullptr;

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
        /*
        output = new Graphviz(name, Graphviz::GRAPH_TEXT, type);

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
        //output->output(this->model);

        // 显示graphviz内部的绘制脚本，而不是dot本身的脚本。
        ostringstream stream;
        stream << "cat " << path;
        auto cmd = stream.str();
        system(cmd.c_str()); */

        ObjGraphviz graphviz("output");
        graphviz.begin_notify();
        for(Object * obj : this->model->get_objs()) {
            graphviz.notify(obj);
        }
        graphviz.end_notify();

    } else { // SVG is default。
/*
        output = new Graphviz(name, Graphviz::GRAPH_SVG, type);

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
        
        // 根据模型产生图片。
        output->output(this->model);

        // 执行显示图片的命令，system必须退出才行。
        ostringstream stream;
        stream << "eog " << path;
        auto cmd = stream.str();
        system(cmd.c_str());
*/
        ObjGraphviz graphviz("output");
        graphviz.begin_notify();
        for(Object * obj : this->model->get_objs()) {
            graphviz.notify(obj);
        }
        graphviz.end_notify();
    }

    return true;
}

bool ProcessCmdLine::init_all_properties(string obj_name, ParseCommandLineWithProperties::Properties properties) {

    for (pair<string, string> one : properties) {
        if (one.first == "name") {
            continue;
        }

        model->add_prop_of_obj(obj_name, one.first, one.second);
    }

    return true;
}
