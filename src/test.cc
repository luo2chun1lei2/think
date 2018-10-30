#include "test.h"

#include <stdio.h>

#include <list>
#include <string>

using namespace std;

#include "subject-observer.h"

// 作为主要的输入输出界面，以及测试程序。
// 对外接口是C语言的，不能是C++的。

//////////////////////////////////////////////////
// 对象基类以及子类

class TObject;

class IContext
{
public:
	static IContext * get_context();
	virtual void add(TObject * t) = 0;
	virtual void dump() = 0;
};

class TObject
{
public:
	TObject() //const char *name
	{
		this->name = "123";
		IContext::get_context()->add(this);
	}
	
	string get_name() {
		return name;
	}
protected:
	string name;
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

/**
 * Object运行的环境，在一个环境中，Object之间可以交流。
 */
class TContext : public IContext
{
public:
	TContext() {}
	virtual void add(TObject * t) {
		list<TObject *>::iterator itr;
		for(itr = inner_list.begin(); itr != inner_list.end(); itr ++) {
			if ( *itr == t ) {
				// already attached, so exit.
				return;
			}
		}
		inner_list.push_back(t);
	}
	
	virtual void dump() {
		// open a file.
		FILE * f = fopen("tmp.dot", "w+");
		if (f == NULL) {
			printf("Cannot create a file.\n");
			return;
		}
		
		// write the node and relations by traveling the context.
		list<TObject *>::iterator itr;
		for(itr = inner_list.begin(); itr != inner_list.end(); itr ++) {
			TObject *obj = *itr;
			string name = obj->get_name();
			fwrite(name.c_str(), name.size(), 1, f);
			fwrite("\n", 1, 1, f);
			//printf("%s\n", name.c_str());
		}
		
		// close the file.
		fclose(f);
	}
protected:
	list<TObject *> inner_list;
private:
};

TContext global_context;
IContext * IContext::get_context()
{
	return &global_context;
}

void test1(bool);
void test_dump()
{
	test1(true);
}

///////////////////////////////////////////////////////////

void test()
{
    test1(true);
}

// 编写的例子1，满足如下的数学公式。
// a = b^2 - 1
void test1(bool need_dump)
{    
    TValue b;
    TValue b_square;
    TValue b_square_minus_1;
    TValue a;

    RSquare r1(b_square, b);
    RAdd r2(b_square_minus_1, b_square, -1);
    REqual r3(a, b_square_minus_1);

    b.assign( 10 );
    
    if (need_dump) {
    	global_context.dump();
    } else {
    	printf("%d=%d^2-1\n", a.value(), b.value());
    	printf("middle value=%d, %d\n", b_square.value(), b_square_minus_1.value());
    }
}