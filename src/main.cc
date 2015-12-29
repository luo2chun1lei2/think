#include <stdio.h>

#include <list>

#include "robject.h"

using namespace std;

/**
 * 桩对象。
 * 模仿临时的、不存在的对象。
 */
class RStub : public RObject
{
private:
protected:
public:
	virtual void set_value(BData * pdata) {
		printf("RStub set_value\n");
		RObject::set_value(pdata);
	}
	
	virtual BData * get_value() {
		printf("RStub get_value\n");
		return RObject::get_value();
	}
};

/**
 * 数据对象。
 */
class RValue : public RObject
{
private:
protected:
public:
	RValue() {
		BData * pd = new BData(0);
		set_value(pd);
	}

	RValue(float f) {
		BData * pd = new BData(f);
		set_value(pd);
	}
	
	virtual ~RValue() {
		//BData * pd = get_value();
		//delete(pd);
		printf("~RValue %p\n", this);
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
	
	virtual void on_notify(RSubject * subject) {
		RObject * po = (RObject *)subject;
		poutput->set_value( new BData( po->get_value()->get_float() ) );
		
		printf("equal's output is %f\n", poutput->get_value()->get_float());
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
	
	virtual void on_notify(RSubject * subject) {
		if( !poutput ) {
			printf("Observer is NOT existed.\n");
			return;
		}
	
		// 需要判断是哪个subject发生了变化。
		float v;
		if(subject == pvalue1) {
			v = pvalue1->get_value()->get_float() * pvalue2->get_value()->get_float();
		} else if(subject == pvalue2) {
			v = pvalue1->get_value()->get_float() * pvalue2->get_value()->get_float();
		} else {
			printf("Changed subject is NOT observered by me.\n");
			return;
		}
		
		printf("multiple result is %f * %f => %f\n", pvalue1->get_value()->get_float(), pvalue2->get_value()->get_float(), v);
		poutput->set_value( new BData(v) );
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
	
	// 需要分清楚是哪个对象发生了变化。
	virtual void on_notify(RSubject * subject) {
};
*/

int main(int argc, char * argv[]) {
	// 首先实现基本的公式测试。
	// E = mc^2;
	RValue e, m, c;
	
	RStub v1, v2;

	BData data1(2.0f), data2(3.0f);

	RelMul * power = new RelMul(&c, &c); // v1 = c * c
	power->set_outer(&v1);

	RelMul * mul = new RelMul(&m, &v1); // v2 = m * v1
	mul->set_outer(&v2);

	RelEqual * equal = new RelEqual(&v2); // e = v2
	equal->set_outer(&e);

	c.set_value(&data1);	// 临时对象放入，恐怕无法保留
	printf("c is %f\n", c.get_value()->get_float());
	
	m.set_value(&data2);
	printf("m is %f\n", m.get_value()->get_float());
	
	printf("e is %f\n", e.get_value()->get_float());
	
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