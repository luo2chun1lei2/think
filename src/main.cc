/**
 * 基本规则：
 * 1. 语言中所有的对象都可以称为“元素”（Element）。
 * 2. 关系也是一种元素，它是多个元素之间的联系。
 *   1. 关系一旦建立，就需要维护。
 * 3. 可以根据元素的关系找到其他的元素。
 * 4. 当获取一个元素时，需要根据关系找到需要的元素。【实际上描述的是延迟生成】
 *
 * 脚本语言
 * elm1.name = zhang
 * elm2.name = li
 * teach(teacher=zhang, student=li) // “张”教“李”
 * ? elm1.student // 查询是 li.
 * ? elm2.teacher   // 查询是 zhang.
 * 
 * TODO 如果是三个对象之间的关系，如何用类似属性的方式定位关联关系？
 *   直角三角形勾股定理 c^2 = a^2 + b^2
 *   c.勾股定理.a
 *   c.勾股定理.b
 *   先找到关系，然后定位关系中的那个元素，反过来推到两元关系
 *   zhang.教学.学生 == li
 *   li.教学.老师 == zhang    
 * TODO 不过这里的语义应该是“被教学”，其实只有两元关系才有正关系和反关系，
 *   对于三元以上的关系，其实没有什么所谓正反关系。
 * 
 * TODO 同一个类型的关系，可能出现在一个对象中，如果都用关系的名称来定位，
 *   那么肯定会重复。比如 校长管理老师，老师管理学生，这样老师就有两个管理关系，
 *   怎么区分？
 *
 * 具体实现
 * 参考代码。
 */

#include <iostream>
 
#include "element.h"

using namespace std;

void info(TElement *elm)
{
	if (elm) {
		cout << "element:" <<  elm << "," << elm->info() << endl;
	} else {
		cout << "element is NULL" << endl;
	}
}

/**
 * 描述 张老师，教，李学生。
 */
void test_1()
{
	TRelation * tmp_rel;
	
	TValue v1("zhang");
	TValue v2("li");
	
	TElement e1;
	TRelation e1_r1;
	
	// elm1.name = zhang
	// TODO 这种关系可以做成一个专门的关系 “own”。
	e1_r1.setElement("from", &e1);
	e1_r1.setElement("name", &v1);
	
	TElement e2;
	TRelation e2_r1;
	
	// elm2.name = li
	e2_r1.setElement("from", &e2);
	e2_r1.setElement("name", &v2);
	
	TRelation r1;
	// teach(teacher=zhang, student=li)
	// TODO 很奇怪不是吗？e1的学生是e2，e2的老师是e1，正好和这个关系的设定相反。这个非常值得研究！
	r1.setElement("teacher", &e1);
	r1.setElement("student", &e2);
	
	// ? elm1.name
	tmp_rel = e1.getRelation("name");
	if (tmp_rel == NULL) {
		cout << "Cannot find name of e1." << endl;
		return;
	}
	info(tmp_rel->getElement("name"));
	
	// ? elm1.student
	tmp_rel = e2.getRelation("student");
	info(tmp_rel);
}
   
int main(int argc, char * argv[])
{
	test_1();
	return 0;
}
