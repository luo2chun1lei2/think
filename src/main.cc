#include <cstdio>
#include <stdlib.h>

#include <list>

#include "subject-observer.h"
#include "console.h"

using namespace std;

// 作为主要的输入输出界面，以及测试程序。
// 对外接口是C语言的，不能是C++的。

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

#include <getopt.h>

static const struct option long_options[] = {
		{"console", 0, NULL, 'c'},
		{"test", 0, NULL, 't'}
};

void usage(void)
{
	printf("think [--test/-t] [--console/-c]\n");
	printf("  --test, -t : run test cases.\n");
	printf("  --console, -c : go into console mode.\n");
}

void test();
void console();

int main(int argc, char *argv[])
{
	// 分析参数，调用具体的功能。
	int opt=0;
	opterr=0;//关闭getopt错误信息
	while((opt = getopt_long(argc, argv, "nc", long_options, NULL))!=-1) {
		switch(opt) {
		case 't':
			//printf("The number is %s\n", optarg);
			// 进入测试模式。
			test();
			break;
		case 'c':
			//printf("The clients is %s\n", optarg);
			// 进入控制台模式。
			console_loop();
			break;
		default:
			usage();
			exit(1);
			break;
		}
	}
	return 0;
}

void test()
{
    test1();
}
