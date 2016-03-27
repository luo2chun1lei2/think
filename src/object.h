#ifndef __T_OBJECT_H__
#define __T_OBJECT_H__

#include <list>
#include <string>

using namespace std;

class TRelation;

class TObject
{
private:

protected:
	list<TRelation *> relations;

public:
	TObject();
	virtual ~TObject();
	
	virtual void set_rel(TRelation * rel);
	virtual TRelation * get_rel(TRelation * rel);
};

class TRelation : public TObject
{
private:
protected:
public:
};

#endif //__T_OBJECT_H__
