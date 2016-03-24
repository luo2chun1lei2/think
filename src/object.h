#ifndef __T_OBJECT_H__
#define __T_OBJECT_H__

#include <list>
#include <string>

using namespace std;

/**
 * 对象有许多属性。
 * 每个属性都有一个名字和一个值对象。
 * 值对象也是一个对象。
 *
 * 注意：一切都是属性。
 */
 
class TObject;

class TProperty
{
private:
protected:
public:
	virtual string get_name() = 0;
	virtual void set_name(string name) = 0;
	
	virtual TObject *get_obj() = 0;
	virtual void set_obj(TObject *obj) = 0;
};

class TObject
{
private:

protected:
	list<TProperty *> properties;

public:
	TObject();
	virtual ~TObject();
	
	void set_property(TProperty * prop);
};

class TKeyValue : public TProperty
{
private:
protected:
public:
	void set(const string key, string value);
	void set(const string key, int value);
};

class TRelation : public TProperty, TObject
{
private:
protected:
public:
};

#endif //__T_OBJECT_H__
