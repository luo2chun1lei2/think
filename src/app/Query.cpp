#include <Query.hpp>

#include <Misc.hpp>

using namespace std;

Query::Query(const std::string name) {
    this->name = name;
}

Query::~Query() {
}

// TODO: 这里的返回值，有问题。
std::string Query::query(const Model *model, const std::string expr) {
    // LOGI("-->%s\n", expr.c_str());

    ParseExpr parse = ParseExpr();

    if (!parse.parse(expr)) {
        LOGE("Expr(%s) is NOT valid.\n", expr.c_str());
        return "error";
    }

    ParseExpr::Path path = parse.get_path();

    Element *elm = nullptr;
    for (auto p : path) {
        if (elm == nullptr) {
            vector<Element *> found = model->find_elm(p);
            if (found.size() != 1) {
                LOGE("No or multiple Elments have name(%s).\n", p.c_str());
                return "error";
            }

            elm = found[ 0 ];
        } else {
            vector<Element *> found = model->find_elm_by_rlt(elm->get_name(), p);
            if (found.size() != 1) {
                LOGE("Elment(%s) have no or multiple relations(%s).\n", elm->get_name().c_str(), p.c_str());
                return "error";
            }
            elm = found[ 0 ];
        }
    }

    return elm->get_name();
}
