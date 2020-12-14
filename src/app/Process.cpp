#include <Process.hpp>

#include <Misc.hpp>

using namespace std;

bool ProcessCmdLine::exec(const std::string cmd) {
	ParseCommandLineWithProperties parse;
	
	if (!parse.parse(cmd)) {
		return false;
	}
	
	string elm_class = parse.get_start();
	ParseCommandLineWithProperties::Properties properties = parse.get_properties();
	
	string name = parse.get_prop_value("name");
	if (name.empty()) {
		LOGE("At least set name of object.\n");
		return false;
	}
	
	if (elm_class == "Model") {
		Model *model = new Model(name);
		this->set_model(model);
		return true;
	} else if(elm_class == "Output") {
		Output *output = new OutputGraphviz(name);	// TODO: special output
		set_output(output);
		return true;
	} else if(elm_class == "Element") {
		Element *elm = new Element(name);
		model->add_elm(elm);
		return true;
	} else if(elm_class == "Relation") {
		Relation *rlt = new Relation(name);
		model->add_elm(rlt);
		return true;
	} else if(elm_class == "query") {
		// TODO: no impl
		return true;
	} else if(elm_class == "clear") {
		// TODO: no impl
		return true;
	}
	
	LOGE("Unknown(%s) type or operation.\n", elm_class.c_str());
	return false;	
}
