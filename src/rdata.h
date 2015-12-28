#ifndef __RDATA_H__
#define __RDATA_H__

#include <list>
#include <string>

using namespace std;

/**
 * 通用数据。
 * 用于对象之间的数据交换。
 * 其本身并不是对象，无法被监视。
 */
class RData
{
private:
protected:
	int iv;
	float fv;
	string sv;
	
public:
	enum Type {
		Integer = 0,
		Float = 1,
		String = 2,
		//TODO 只有这些类型吗？
	};
	
protected:
	Type type;
	
public:
	
	RData(int v) {
		type = Integer;
		iv = v;
	}
	
	RData(float v) {
		type = Float;
		fv = v;
	}
	
	RData(string v) {
		type = String;
		sv = v;
	}
	
	virtual ~RData() {
		// 释放什么？
		printf("~RData %p\n", this);
	}
	
	Type get_type() {
		return type;
	}
	
	string get_string() {
		return sv;
	}
	
	int get_int() {
		return iv;
	}
	
	float get_float() {
		return fv;
	}
	
	void set_float(float v) {
		type = Float;
		fv = v;
	}
	
	void set_int(int v) {
		type = Integer;
		iv = v;
	}
	
	void set_str(string v) {
		type = String;
		sv = v;
	}
};

#endif //__RDATA_H__
