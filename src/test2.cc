/**
 * 主要验证数据关系，
 * 以学生、老师、班级之间的关系为主要描述对象。
 */
#include <stdio.h>

#include <list>
#include <string>

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
    // owner拥有owned。
    RObject * owner;
    RObject * owned;

public:
	ROwn(string ownerName, RObject * owner, string ownedName, RObject * owned) {
        this->owner = owner;
        owner->addRelation(ownerName, this);

        this->owned = owned;
        owned->addRelation(ownedName, this);
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
    RObject * owner;
public:
    RGroup(string name, RObject * owner) {
        this->owner = owner;
        owner->addRelation(name, this);
    }
    virtual ~RGroup() {}

    virtual void onNotify(RSubject * subject) {
    }
};

int test_2() {

    // 先定义了一堆对象。
	Student * zhangSan = new Student();
	Student * liSi = new Student();

    Class * c14 = new Class();
	
	Teacher * wang = new Teacher();
	
    // 开始建立关系。
	ROwn * own1 = new ROwn("has", c14, "re-has", zhangSan);
	ROwn * own2 = new ROwn("has", c14, "re-has", liSi);

    // 用一个组关系，管理上面的关系。
    RGroup * group1 = new RGroup("has", c14);

    // 都加入到同一个“include”关系组中。
    group1->addRelation("include", own1);   // 这里的include 有用吗？
    group1->addRelation("include", own2);

    //c14->addRelation("has", group1);

    ROwn * own3 = new ROwn("teach", wang, "re-teachre", c14);

	return 0;
}

/**
 * TODO
 * 1. 关系添加到对象中时，需要在两边都有名字，供查询。
 * 1. group关系是包含多个关系的关系，所以被它包含的对象也需要一个名字。
 *      这样是不是容易造成名字出现重复，因为被包含的关系本身最好是不要知道自己被包含了，
 *      但是实际上，还是需要知道，需要双方相互之间引用。
 * 1. 关系如何组成成新的关系？表面上应该是一个关系。
 */

