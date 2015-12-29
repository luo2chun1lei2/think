#ifndef __RDATA_H__
#define __RDATA_H__

#include <math.h>
#include <list>
#include <string>
#include <sstream>

using namespace std;

/**
 * 基础数据，仅仅用于对象之间的数据交换。
 * 其本身并不是对象，无法被监视。
 */
class BData
{
private:
protected:
	int iv;
	float fv;
	string sv;
	
public:
	enum Type {
		None = 0,
		Integer = 1,
		Float = 2,
		String = 3,
		//TODO 只有这些类型吗？
	};
	
protected:
	Type type;
	
public:
	
	BData(int v) {
		type = Integer;
		iv = v;
	}
	
	BData(float v) {
		type = Float;
		fv = v;
	}
	
	BData(string v) {
		type = String;
		sv = v;
	}
	
	virtual ~BData() {
		// 释放什么？
		printf("~BData %p\n", this);
	}
	
	Type get_type() {
		return type;
	}
	
	string get_string() {
		if(type == Integer) {
			stringstream ss;
			ss << iv;
			return ss.str();
		} else if(type == Float) {
			stringstream ss;
			ss << fv;
			return ss.str();
		} else if(type == String) {
			return sv;
		} else { //None
			return string("");
		}
	}
	
	int get_int() {
		if(type == Integer) {
			return iv;
		} else if(type == Float) {
			return lrint(fv);
		} else if(type == String) {
			int v;
			stringstream ss;
			ss << sv;
			ss >> v;
			if( ss.good() ) {
				return v;	
			} else {
				return 0;
			}
		} else { //None
			return 0;
		}
	}
	
	float get_float() {
		if(type == Integer) {
			return iv;
		} else if(type == Float) {
			return fv;
		} else if(type == String) {
			float v;
			stringstream ss;
			ss << sv;
			ss >> v;
			if( ss.good() ) {
				return v;
			} else {
				return 0;
			}
		} else { //None
			return 0;
		}
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
