/**
 * 主要验证数据关系，
 * 以学生、老师、班级之间的关系为主要描述对象。
 */
#include <stdio.h>

#include <list>

#include "robject.h"

using namespace std;

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

class Class: public RObject {
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

    virtual void onNotify(RSubject * subject) {
    }
};

int test_2() {


	// 建立对象
	Student * zhangSan = new Student();
	
	Teacher * liSi = new Teacher();
	
	// 建立相互之间的关系
	Teach * teach1 = new Teach(liSi, zhangSan);
	
	// 可以根据其中一个对象和关系，找到相关的对象。
	// -可以根据老师找到教导的学生。
	// -可以根据学生，找到教导他的老师。
	
	// 可以根据两人，找到他们之间的关系。
	// 可以根据关系，找到符合条件的对象对。


	return 0;
}

