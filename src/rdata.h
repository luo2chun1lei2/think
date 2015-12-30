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
	BData() {
		type = None;
	}
	
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
		//printf("~BData %p\n", this);
	}
	
	Type getType() {
		return type;
	}
	
	void setStr(string v) {
		type = String;
		sv = v;
	}
	
	string getStr() {
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
	
	void setInt(int v) {
		type = Integer;
		iv = v;
	}
	
	int getInt() {
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
	
	void setFloat(float v) {
		type = Float;
		fv = v;
	}
	
	float getFloat() {
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
	
};

/**
 * 具有设定一个Data值的类。
 */
class BValue {
private:
protected:
	BData value;
	
public:
	virtual void setValue(BData data) {
		value = data;
	}
	
	// TODO 性能是否可以优化？
	virtual BData getValue() {
		return value;
	}
};

#endif //__RDATA_H__
