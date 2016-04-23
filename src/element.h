#ifndef __T_ELEMENT_H__
#define __T_ELEMENT_H__

#include <list>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class TRelation;

/**
 * 元素，所有对象的基类。
 * TODO 每个元素都应该具有一个全局唯一的名字？
 */
class TElement
{
private:

protected:
	// 需要根据名字找到元素的关系，虽然是一个关系，
	// 针对不同的元素却有不同的名字。
	// 比如 李的老师是张，张的学生是李，中间的关系“的老师”和“的学生”实际上一个。
	typedef map<string, TRelation *> Relations;
	
	Relations relations;

public:
	TElement() 
	{
	}
	
	virtual ~TElement()
	{
	}
	
	/**
	 * 返回此对象的信息。
	 * TODO 是否返回其他对象的信息？
	 */ 
	virtual void info(int level)
	{
		cout << "Element(";
		
		Relations::iterator iter;
		bool added = false;
		for(iter = relations.begin(); iter != relations.end(); iter++) {
			if (level <= 0) {
				if (iter->first != "name") {
					// 只输出“name”
					continue;
				}
			}
			
			if (added) {
				cout << ",";
			}
			
			cout << iter->first << ":";
			((TElement *)iter->second)->info(--level);
			
			added = true;
		}
		
		cout << ")";
	}
	
	/**
	 * 添加一个关系，如果名字相同，就合成一个。
	 */
	virtual void setRelation(string key, TRelation *rel) 
	{
		relations.insert(Relations::value_type(key, rel));
	}
	
	/**
	 * 删除指定Key的关系。
	 */
	virtual void delRelation(string key)
	{
		relations.erase(key);
	}
	
	/**
	 * 找到一个关系。
	 */
	virtual TRelation * getRelation(string key)
	{
		Relations::iterator iter = relations.find(key);
		if (iter == relations.end()) {
			return NULL;
		} else {
			return iter->second;
		}
	}
	
};

/**
 * 所有关系的基类，可以连接多个对象。
 */
class TRelation : public TElement
{
private:
protected:
	typedef map<string, TElement *> Elements;
	Elements elements;
	
public:

	TRelation() : TElement()
	{
	}
	
	virtual ~TRelation()
	{
	}
	
	virtual void info(int level)
	{
		cout << "Relation(";
		
		Elements::iterator iter;
		bool added = false;
		for(iter = elements.begin(); iter != elements.end(); iter++) {
			if (level <= 0) {
				if (iter->first != "name") {
					// 只输出"name"
					continue;
				}
			}
			
			if (added) {
				cout << ",";
			}
			
			cout << iter->first << ":";
			iter->second->info(--level);
			
			added = true;
		}
		
		cout << ")";
	}

	virtual void setElement(string key, TElement * elm) 
	{
		elements.insert(Elements::value_type(key, elm));
		// elements[key] = elm;
	}
	
	/**
	 * 删除制定key的关系。
	 */
	virtual void delElement(string key)
	{
		elements.erase(key);
	}
	
	virtual TElement * getElement(string key)
	{
		Elements::iterator iter = elements.find(key);
		if (iter == elements.end()) {
			return NULL;
		} else {
			return iter->second;
		}
	}
};

/**
 * 值元素。
 * 所有的值，比如整数、文字、浮点数等都用这个类型来表示。
 */
class TValue : public TElement
{
private:
protected:
	string value;
public:
	TValue(string value)
	{
		this->value = value;
	}
	
	virtual ~TValue()
	{
	}
	
	virtual void info(int level)
	{
		cout << "Value(" << value;
		
		Relations::iterator iter;
		bool added = false;
		for(iter = relations.begin(); iter != relations.end(); iter++) {
		
			if (level <= 0) {
				if (iter->first != "name") {
					// 只输出“name”
					continue;
				}
			}
			
			if (added) {
				cout << ",";
			}
			
			cout << iter->first << ":";
			iter->second->info(--level);
			
			added = true;
		}
		
		cout << ")";
	}
	
	void setString(string v)
	{
		this->value = v;
	}
	
	string getString()
	{
		return this->value;
	}
};

#endif //__T_ELEMENT_H__
