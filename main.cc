#include <stdio.h>

#include <list>

using namespace std;

class RObject {
private:
protected:
public:
	RObject() {
	}
	
	virtual ~RObject() {}
};

class RRelation {
private:
protected:
public:
	RRelation() {}
	virtual ~RRelation() {}
};

class RGlobal {
private:
protected:
	list<RObject *> objs;
	list<RRelation *> relations;
	
public:
	RGlobal() {}
	
	virtual void add(RObject * obj) {
		objs.push_back(obj);
	}
	
	virtual void del(RObject * obj) {
		objs.remove(obj);
	}
	
	virtual void add(RRelation * rel) {
		relations.push_back(rel);
	}
	
	virtual void del(RRelation * rel) {
		relations.remove(rel);
	}
	
	virtual ~RGlobal() {}
};

//-----------------------------
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
	
	virtual ~Teach() {
	}
};

int main(int argc, char * argv[]) {
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
	
	// 找到所有的关系
	
	// 可以根据其中一个对象和关系，找到相关的对象。
	// -可以根据老师找到教导的学生。
	// -可以根据学生，找到教导他的老师。
	
	// 可以根据两人，找到他们之间的关系。
	// 可以根据关系，找到符合条件的对象对。	
	
	return 0;
}

