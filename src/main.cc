#include <stdio.h>

#include <list>

#include "robject.h"

using namespace std;

class RStub : public RObject
{
private:
protected:
	float value;
public:
	virtual void set_value(float v) {
		value = v;
		
		raise_changed( &value );
	}
	
	virtual float get_value() { 
		return value;
	}
};

class RFloat : public RObject
{
private:
protected:
	float value;
public:
	RFloat() {value = 0;}
	
	// TODO 应该尽量将设定变成通用的方法，而不是针对特定类型的。
	virtual void set_value(float v) {
		value = v;
		
		// send changed signal.
		raise_changed( &value );
	}
	
	virtual float get_value() {
		return value;
	}
};

class RelEqual: public RRelation
{
private:
protected:
	RObject* pvalue;
public:
	RelEqual(RObject* po) {
		pvalue = po;
		
		pvalue->register_observer(this);
	}
	
	virtual void on_notify(void *pdata) {
		poutput->set_value( *(float *)pdata);
	}
};

class RelMul: public RRelation
{
private:
protected:
	RObject* pvalue1;
	RObject* pvalue2;
public:
	RelMul(RObject* po1, RObject* po2) {
		pvalue1 = po1;
		pvalue2 = po2;
		
		pvalue1->register_observer(this);
		pvalue2->register_observer(this);
	}
	
	virtual void on_notify(void *pdata) {
		// TODO 谁的数据被修改了？
		float v = pvalue1->get_value() * pvalue2->get_value();
		
		poutput->set_value( v );
	}
};

/*
class RelPower: public RRelation
{
private:
protected:
	RObject * pvalue1;
	RObject * pvalue2;
public:
	RelPower(RObject* po1, RObject* po2): pvalue1(po1), pvalue2(po2) {
	}
};
*/

int main(int argc, char * argv[]) {
	// 首先实现基本的公式测试。
	// E = mc^2;
	RFloat e, m, c;
	RStub v1, v2;
	
	RelMul * power = new RelMul(&c, &c); // v1 = c * c
	power->set_outer(&v1);
	
	
	RelMul * mul = new RelMul(&m, &v1); // v2 = m * v1
	mul->set_outer(&v2);
	
	RelEqual * equal = new RelEqual(&v2); // e = v2
	equal->set_outer(&e);
	
	c.set_value(2);
	m.set_value(3);
	
	printf("result = %f\n", e.get_value());
	return 0;
}

///////////////////////////////////////////////////////////

#if 0

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

#endif