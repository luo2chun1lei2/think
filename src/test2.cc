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

/**
 * 所属关系。
 * 建立一个对象的属性的基本关系。
 */
class ROwn: public RRelation {
private:
protected:

public:
	ROwn() {
	}

	virtual ~ROwn() {}

    virtual void onNotify(RSubject * subject) {
    }
};

int test_2() {

	Student * zhangSan = new Student();
	
	Teacher * liSi = new Teacher();
	
	ROwn * teach1 = new ROwn(zhangSan);

	return 0;
}

