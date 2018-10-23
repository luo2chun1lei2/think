#pragma once

/**
 * 数值元素，只完成基本的数值动作，不具有对象的功能。
 */
class VValue
{
public:
    VValue() {}
    VValue(int v) {
    	this->value = v;
    }
    virtual ~VValue() {}
    
    int intValue() {
    	return value;
    }
    
    void setIntValue(int v) {
    	this->value = v;
    }
protected:
	int value;
private:
};