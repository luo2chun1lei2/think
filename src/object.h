#ifndef __T_OBJECT_H__
#define __T_OBJECT_H__

#include <list>
#include <map>
#include <string>

using namespace std;

class TRelation;

class TObject
{
private:

protected:
	typedef map<string, TRelation *> Relations;
	Relations relations;

public:
	TObject();
	virtual ~TObject();
	
	virtual void setRelation(string key, TRelation *obj) 
	{
		relations.insert(Relations::value_type(key, obj));
	}
	virtual TRelation * getRelation(string key) {
		Relations::iterator iter = relations.find(key);
		if (iter == relations.end()) {
			return NULL;
		} else {
			return iter->second;
		}
	}
};

/**
 * 关系有多种类型，
 * 一种是 一对多，多对多之类的。
 * 一类的是功能：拥有、相等等。
 */
class TRelation : public TObject
{
private:
protected:
	typedef map<string, TObject *> Objects;
	Objects objects;
	
public:
	virtual void setObject(string key, TObject * obj) {
		objects.insert(Objects::value_type(key, obj));
	}
	virtual TObject * getObject(string key) {
		Objects::iterator iter = objects.find(key);
		if (iter == objects.end()) {
			return NULL;
		} else {
			return iter->second;
		}
	}
};

class TString : public TObject
{
private:
protected:
	string value;
public:
	TString(string value) {
		this->value = value;
	}
	
	void setValue(string v) {
		this->value = v;
	}
	
	string getValue() {
		return this->value;
	}
};

#endif //__T_OBJECT_H__
