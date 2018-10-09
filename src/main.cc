#include <cstdio>

#include <list>

using namespace std;

// 作为主要的输入输出界面，以及测试程序。
// 对外接口是C语言的，不能是C++的。

//////////////////////////////////////////////////

/**
 * 数值元素，只完成基本的数值动作，不具有对象的功能。
 */
class VValue
{
public:
    VValue() {}
    VValue(int v) {
    	this->value = v;
    }
    virtual ~VValue() {}
    
    int intValue() {
    	return value;
    }
    
    void setIntValue(int v) {
    	this->value = v;
    }
protected:
	int value;
private:
};

//////////////////////////////////////////////////
// 注册和通知（Event)

class ESubject;

class EObserver
{
public:
	// 接受者需要知道来源，才能正确的处理多个内部元素的问题。
	virtual void update(ESubject * sub, VValue &value) = 0;
protected:	
private:
};

/**
 * 发送信息方。自身有改变通知观察者(Observer)。
 */
class ESubject
{
public:
	typedef list<EObserver *> obs_list_t;
	virtual void attach(EObserver * obs) {
		obs_list_t::iterator itr;
		for(itr = observers.begin(); itr != observers.end(); itr ++) {
			if ( *itr == obs ) {
				// already attached, so exit.
				return;
			}
		}
		observers.push_back(obs);
	}
	
	virtual void detach(EObserver *obs) {
		obs_list_t::iterator itr;
		
		for(itr = observers.begin(); itr != observers.end(); itr ++) {
			if ( *itr == obs ) {
				observers.erase(itr);
				break;
			}
		}
		
	}
	// 当subject发生变化后，通知所有的observer。
	virtual void notify(VValue &value) {
		obs_list_t::iterator itr;
		for(itr = observers.begin(); itr != observers.end(); itr ++) {
			(*itr)->update(this, value);
		}
	}
protected:
	list<EObserver *> observers;
private:
};

//////////////////////////////////////////////////
// 对象基类以及子类

class TObject
{
public:
protected:
private:
};

// 是公式中的值
// 当值修改后，需要发出修改的信号。
class TValue : public TObject, public ESubject //, EObserver
{
public:
    TValue() {
        this->v = 0;
    }
    TValue(int v) {
        this->v = v;
    }
    virtual ~TValue() {}

    int value()
    {
        return v;
    }

	// 当修改内部的数据后，需要通知所有观察者。
    void assign(int v)
    {
    	if (this->v != v) {
	        this->v = v;
	        VValue vvalue(this->v);
	        notify(vvalue);
	    }
    }
    
    // 当被观察
    // interface of EObserver
    /* 也许这个是不需要的。
    virtual void update(VValue &value) {
    	this->v = value.intValue();
    	VValue vvalue(this->v);
    	notify(value);
    } */
    
protected:
private:
    int v;
};

class TRelation: public TObject, public EObserver
{
public:
protected:
private:
};

// 父类EObserver，需要监视内部的对象。
class REqual : public TRelation
{
public:
    REqual(TValue &left, TValue &right) : left(left), right(right) {
    	this->right.attach(this);
    }
    
    // interface of EObserver
    virtual void update(ESubject * sub, VValue &value) {
    	this->left.assign(value.intValue());	
    }
protected:
private:
    TValue & left;
    TValue & right;
};

class RSquare : public TRelation
{
public:
    RSquare(TValue &square, TValue &v) : v(v), square(square) {
    	this->v.attach(this);	
    }
    
    // interface of EObserver
    virtual void update(ESubject * sub, VValue &value) {
    	int one = value.intValue();
    	this->square.assign( one * one );	
    }
    
protected:
private:
    TValue & v;
    TValue & square;
};

//class RArithmetic : public TRelation
class RAdd : public TRelation
{
public:
    RAdd(TValue &sum, TValue &v, int added) : v(v), added(added), sum(sum) {
    	v.attach(this);
    }
    
    // interface of EObserver
    virtual void update(ESubject * sub, VValue &value) {
    	int one = value.intValue();
    	this->sum.assign( one + added );	
    }
    
protected:
private:
    TValue & v;
    int added;
    TValue & sum;
};

/*
class RMulti : public TRelation
{
public:
	RMulti(TValue
protected:
private:
};
*/
//////////////////////////////////////////////////

// 编写的例子1，满足如下的数学公式。
// a = b^2 - 1
void test1()
{    
    TValue b;
    TValue b_square;
    TValue b_square_minus_1;
    TValue a;

    RSquare r1(b_square, b);
    RAdd r2(b_square_minus_1, b_square, -1);
    REqual r3(a, b_square_minus_1);

    b.assign( 10 );
    printf("%d=%d^2-1\n", a.value(), b.value());
    printf("middle value=%d, %d\n", b_square.value(), b_square_minus_1.value());
}

int main()
{
    printf("input rthink's console:\n");
    
    test1();
    
    return 0;
}
