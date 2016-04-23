#include "element.h"

using namespace std;

void info(TElement *elm, int level)
{
	if (elm) {
		elm->info(level); 
		cout << endl;
	} else {
		cout << "element is NULL" << endl;
	}
}

/**
 * 描述 张老师，教，李学生。
 */
void test_1()
{
	TRelation * tmp_rel;	// 临时的关系
	
	////////////////////////////////////////////////////////// 定义变量
	
	TElement e1;			// 张三
	TValue v1("zhang");		// 张三名字
	TRelation e1_r1;		// 张三拥有名字的关系
	
	TElement e2;			// 李四
	TValue v2("li");		// 李四名字
	TRelation e2_r1;		// 李四拥有名字的关系
	
	TRelation r1;			// 教授关系
	
	////////////////////////////////////////////////////////// 设定关系
	
	// elm1.name = zhang
	// TODO 这种关系可以做成一个专门的关系 “own”。
	e1_r1.setElement("from", &e1);
	e1.setRelation("name", &e1_r1);
	e1_r1.setElement("name", &v1);
	v1.setRelation("from", &e1_r1);
	
	// elm2.name = li
	e2_r1.setElement("from", &e2);
	e2.setRelation("name", &e2_r1);
	e2_r1.setElement("name", &v2);
	v2.setRelation("from", &e2_r1);
	
	// teach(teacher=zhang, student=li)
	// TODO 很奇怪不是吗？e1的学生是e2，e2的老师是e1，正好和这个关系的设定相反。这个非常值得研究！
	r1.setElement("teacher", &e1);
	r1.setElement("student", &e2);
	
	// elm1.student = rel
	e1.setRelation("student", &r1);
	// elm2.teacher = rel
	e2.setRelation("teacher", &r1);
	
	////////////////////////////////////////////////////////// 开始查询
	
	// ? elm1.name
	info(&e1, 2);
	tmp_rel = e1.getRelation("name");
	if (tmp_rel == NULL) {
		cout << "Cannot find name of e1." << endl;
		return;
	}
	//info(tmp_rel, 2);
	//info(tmp_rel->getElement("name"), 1);
	
	// ? elm1.student
	tmp_rel = e1.getRelation("student");
	//info(tmp_rel, 1);
}
   
int main(int argc, char * argv[])
{
	test_1();
	return 0;
}
