#include <stdio.h>

#include <list>

#include "robject.h"

using namespace std;

/**
 * 数据对象。
 * 其实具体功能都在RObject实现了，这里什么都没有做，还有必要保留这样的一个类型吗？
 */
class RValue : public RObject
{
private:
protected:
public:
	RValue() {
		setValue(BData(0));
	}
};

/**
 * 关系：单向相等。
 */
class RelEqual: public RelOne
{
private:

protected:
	RObject* pfrom;
	
public:
	RelEqual() {}
	virtual ~RelEqual() {
		// TODO 需要对于监视对象进行反注册。
	}

	RelEqual(RObject *to, RObject *from)
	{
		pfrom = from;
		setTo(to);
		
		pfrom->registerObserver(this);
	}
	
	virtual void onNotify(RSubject * subject) 
	{
		RObject * po = (RObject *)subject;
		if(po != pfrom) {
			// 不是从from发出的变化信息，那么出错。
			printf("Error: subject is not from.\n");
			return;
		}
		
		getTo()->setValue( pfrom->getValue() );
		
		//printf("equal's output is %f\n", poutput->get_value()->get_float());
	}
};

class RelMul: public RRelation
{
private:

protected:
	RObject* pfrom1;
	RObject* pfrom2;
	
public:
	RelMul(RObject* from1, RObject* from2) {
		pfrom1 = from1;
		pfrom2 = from2;
		
		pfrom1->registerObserver(this);
		pfrom2->registerObserver(this);
	}
	
	virtual void onNotify(RSubject * subject) {
		
		if(subject != pfrom1 && subject != pfrom2) {
			printf("Error: suject is not from 1 and 2.\n");
			return;
		}
	
		// 不需要区分是哪个对象发出的。
		float v;
		v = pfrom1->getValue().getFloat() * pfrom2->getValue().getFloat();
		value.setFloat(v);
		
		//printf("multiple is %f * %f => %f\n", pfrom1->getValue().getFloat(), pfrom2->getValue().getFloat(), v);
        // 通知监视的模块，我已经改变了。
        raiseChanged();
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

	BData data1(2.0f), data2(3.0f);

	RelMul power(&c, &c); // v1 = c * c

	RelMul mul(&m, &power); // v2 = m * v1

	RelEqual equal(&e, &mul); // e = v2

	c.setValue(data1);	// 临时对象放入，恐怕无法保留
	printf("c^2(%f) = c(%f) * c(%f)).\n", power.getValue().getFloat(), c.getValue().getFloat(), c.getValue().getFloat());
	printf("%f = m(%f) * c^2(%f)).\n", mul.getValue().getFloat(), m.getValue().getFloat(), power.getValue().getFloat());
	printf("E(%f) = (%f).\n", e.getValue().getFloat(), mul.getValue().getFloat());
	
	m.setValue(data2);
	printf("c^2(%f) = c(%f) * c(%f)).\n", power.getValue().getFloat(), c.getValue().getFloat(), c.getValue().getFloat());
	printf("%f = m(%f) * c^2(%f)).\n", mul.getValue().getFloat(), m.getValue().getFloat(), power.getValue().getFloat());
	printf("E(%f) = (%f).\n", e.getValue().getFloat(), mul.getValue().getFloat());
	
	c.setValue(BData(1.1f));
	printf("c^2(%f) = c(%f) * c(%f)).\n", power.getValue().getFloat(), c.getValue().getFloat(), c.getValue().getFloat());
	printf("%f = m(%f) * c^2(%f)).\n", mul.getValue().getFloat(), m.getValue().getFloat(), power.getValue().getFloat());
	printf("E(%f) = (%f).\n", e.getValue().getFloat(), mul.getValue().getFloat());
	
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
