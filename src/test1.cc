/**
 * 主要以测试数学公式为核心。
 */
#include <stdio.h>

#include <list>

#include "robject.h"

using namespace std;

/**
 * 数据对象。
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

class RelMul: public RelOne
{
private:

protected:
	RObject* pfrom1;
	RObject* pfrom2;
	
public:
	RelMul(RObject * to, RObject* from1, RObject* from2) {
		setTo(to);
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
		getTo()->setValue( BData(v) );
		
		//printf("multiple is %f * %f => %f\n", pfrom1->getValue().getFloat(), pfrom2->getValue().getFloat(), v);
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

int test_1()
{
	// 首先实现基本的公式测试。
	// E = mc^2;
	RValue e, m, c;
	
	RValue v1, v2;

	BData data1(2.0f), data2(3.0f);

	RelMul power(&v1, &c, &c); // v1 = c * c

	RelMul mul(&v2, &m, &v1); // v2 = m * v1

	RelEqual equal(&e, &v2); // e = v2

	c.setValue(data1);	// 临时对象放入，恐怕无法保留
	printf("c^2(%f) = c(%f) * c(%f)).\n", v1.getValue().getFloat(), c.getValue().getFloat(), c.getValue().getFloat());
	printf("%f = m(%f) * c^2(%f)).\n", v2.getValue().getFloat(), m.getValue().getFloat(), v1.getValue().getFloat());
	printf("E(%f) = (%f).\n", e.getValue().getFloat(), v2.getValue().getFloat());
	
	m.setValue(data2);
	printf("c^2(%f) = c(%f) * c(%f)).\n", v1.getValue().getFloat(), c.getValue().getFloat(), c.getValue().getFloat());
	printf("%f = m(%f) * c^2(%f)).\n", v2.getValue().getFloat(), m.getValue().getFloat(), v1.getValue().getFloat());
	printf("E(%f) = (%f).\n", e.getValue().getFloat(), v2.getValue().getFloat());
	
	c.setValue(BData(1.1f));
	printf("c^2(%f) = c(%f) * c(%f)).\n", v1.getValue().getFloat(), c.getValue().getFloat(), c.getValue().getFloat());
	printf("%f = m(%f) * c^2(%f)).\n", v2.getValue().getFloat(), m.getValue().getFloat(), v1.getValue().getFloat());
	printf("E(%f) = (%f).\n", e.getValue().getFloat(), v2.getValue().getFloat());
	
	return 0;
}

