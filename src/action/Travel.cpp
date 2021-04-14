#include <Travel.hpp>

#include <vector>

using namespace std;

bool Travel::travel(Object * pobj)
{
    // 记录已经遍历后的对象。
    vector<Object *> dones;

    // 记录还没有遍历的对象。
    vector<Object *> waits;

    do {
        if( typeid(*pobj) == typeid(Relation)) {
            //pobj->get_
        } else {
            
        }
        
    } while(true);

    return true;
}