#pragma once

#include <Element.hpp>
#include <Relation.hpp>

/**
 * 包含若干元素，这些元素和外部的模型没有关系。
 * TODO: 以后必然会融合多个模型，以后模型就是组合元素。
 */
class Model
{
public:
	Model(){}
	Model(const Model &mdl) = delete;
	virtual ~Model(){}
protected:
private:
};