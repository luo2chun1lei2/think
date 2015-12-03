#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include <list>

using namespace std;

/////////////////////////////
class RObject {

private:

protected:

public:
	RObject();
	virtual ~RObject();
};

/////////////////////////////
class RRelation {
private:
protected:
public:
	RRelation() {}
	virtual ~RRelation() {}
};

/////////////////////////////

class RGlobal {
private:
protected:
	list<RObject *> objs;
	list<RRelation *> relations;
	
public:
	RGlobal() {}
	
	virtual void add(RObject * obj) {
		objs.push_back(obj);
	}
	
	virtual void del(RObject * obj) {
		objs.remove(obj);
	}
		
	virtual void add(RRelation * rel) {
		relations.push_back(rel);
	}
	
	virtual void del(RRelation * rel) {
		relations.remove(rel);
	}
	
	virtual ~RGlobal() {}
};

#endif //__CONTAINER_H__

