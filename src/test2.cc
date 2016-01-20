/**
 * 主要验证数据关系，
 * 以学生、老师、班级之间的关系为主要描述对象。
 */
#include <stdio.h>

#include <list>

#include "robject.h"

using namespace std;

// 学生
class Student: public RObject {
private:
protected:
public:
};

// 老师
class Teacher: public RObject {
private:
protected:
public:
};

// 班级信息。
class Class: public RObject {
private:
protected:
public:
};

/**
 * 所属关系。
 * 建立一个对象的属性的基本关系。
 * 当关系发生了变化后，通知监视的对象。
 * TODO 包括什么关系？
 */
class ROwn: public RRelation {
private:
protected:
    RObject * owned;

public:
	ROwn(RObject * owned) {
        this->owned = owned;
	}

	virtual ~ROwn() {}

    virtual void onNotify(RSubject * subject) {
        // 监视owned，当它发生了改变后，引发动作。
        // TODO 什么动作？
    }
};

class RGroup: public RRelation 
{
private:
protected:
public:
    RGroup() {
    }
    virtual ~RGroup() {}

    virtual void onNotify(RSubject * subject) {
    }
};

int test_2() {

	Student * zhangSan = new Student();
	Student * liSi = new Student();

    Class * c14 = new Class();
	
	Teacher * wang = new Teacher();
	
    // 加入了所属关系
	ROwn * own1 = new ROwn(zhangSan);
	ROwn * own2 = new ROwn(liSi);

    // 用一个组关系，管理上面的关系。
    RGroup * group1 = new RGroup();

    group1->addRelation("include", own1);
    group1->addRelation("include", own2);

    c14->addRelation("has", group1);

    ROwn * own3 = new ROwn(c14);
    wang->addRelation("teach", own3);

	return 0;
}

/**
 * TODO
 * 1. student需要一个链接到teach关系吗？不然student无法找到教他的老师。
 * 1. 老师需要教一个班级，而班级拥有学生。
 * 1. 班级如何拥有多个学生？
 */

