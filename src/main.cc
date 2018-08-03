#include <stdio.h>

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
    virtual ~VValue() {}
protected:
private:
};

//////////////////////////////////////////////////

class TObject
{
public:
protected:
private:
};

// 是公式中的值
class TValue : public TObject
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

    void assign(int v)
    {
        this->v = v;
    }
protected:
private:
    int v;
};

class TRelation: public TObject
{
};

class REqual : public TRelation
{
public:
    REqual(TValue &left, TValue &right) : left(left), right(right) {
    }
protected:
private:
    TValue & left;
    TValue & right;
};

class RSquare : public TRelation
{
public:
    RSquare(TValue &v, TValue &square) : v(v), square(square) {
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
    RAdd(TValue &v, int added, TValue &sum) : v(v), added(added), sum(sum) {
    }
protected:
private:
    TValue & v;
    int added;
    TValue & sum;
};

//////////////////////////////////////////////////

// 数值之间有关系。
void test1()
{
    // a = b^2 - 1
    TValue b;
    TValue b_square;
    TValue b_square_1;
    TValue a;

    RSquare r1(b, b_square);
    RAdd r2(b_square, -1, b_square_1);
    REqual r3(b_square_1, a);

    b.assign( 10 );
    printf("%d=%d^2-1\n", a.value(), b.value());
}

int main()
{
    printf("rthink:\n");
    
    test1();
    
    return 0;
}
