#include <stdio.h>

#include <list>

#include "robject.h"

using namespace std;

class ObjNum: public RObject 
{
private:
protected:
	int value;
public:
	ObjNum() {value = 0;}
	
	void set_value(int v) {
		value = v;
	}
	
	int get_value() {
		return value;
	}
};

class RelEqual: public RRelation
{
private:
protected:
	// obj1 = obj2
	RObject & obj1;
	const RObject & obj2;
public:
	RelEqual(RObject & o1, const RObject & o2): obj1(o1), obj2(o2) {
	}
};

class RelAdd: public RRelation
{
private:
protected:
	ObjNum & num1;
	ObjNum & num2;
public:
	RelAdd(ObjNum & n1, ObjNum & n2): num1(n1), num2(n2) {
	}
};

int main(int argc, char * argv[]) {
	// 首先实现基本的公式测试。
	// c <= a + b
	ObjNum a, b, c;
	RelEqual(c, RelAdd(a, b)); // c是a与b的和。
	
	a.set_value(1);
	b.set_value(2);
	printf("result = %d\n", c.get_value());
	return 0;
}

///////////////////////////////////////////////////////////

class Student: public RObject {
private:
protected:
public:
};

class Teacher: public RObject {
private:
protected:
public:
};

class Teach: public RRelation {
private:
protected:
	Teacher * pTeacher;
	Student * pStudent;
public:
	Teach(Teacher *t, Student *s) {
		pTeacher = t;
		pStudent = s;
	}
	
	virtual ~Teach() {}
};

int main1(int argc, char * argv[]) {
	RGlobal global;

	// 建立对象
	Student * zhangSan = new Student();
	global.add(zhangSan);
	
	Teacher * liSi = new Teacher();
	global.add(liSi);
	
	// 建立相互之间的关系
	Teach * teach1 = new Teach(liSi, zhangSan);
	global.add(teach1);
	
	// 找到所有的对象
	global.info_objects();
	
	// 找到所有的关系
	global.info_relations();
	
	// 可以根据其中一个对象和关系，找到相关的对象。
	// -可以根据老师找到教导的学生。
	// -可以根据学生，找到教导他的老师。
	
	// 可以根据两人，找到他们之间的关系。
	// 可以根据关系，找到符合条件的对象对。
	
	printf("end of program.\n");
	
	return 0;
}

