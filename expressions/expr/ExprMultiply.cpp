/*
 * ExprMultiply.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#include "ExprMultiply.h"

#include "ExprZero.h"
#include "ExprAddition.h"
#include "ExprValue.h"
//#include "ExprOne.h"


ExprMultiply::ExprMultiply(ExpressionRename* l, ExpressionRename* r) :
		ExprParent { '*' }
{
	children.push_back(l);
	children.push_back(r);
}

ExprMultiply::ExprMultiply() :
	ExprParent{'*'}
{
}


ExprMultiply::~ExprMultiply() {}


ExprParent* ExprMultiply::newOne() const
{
	return new ExprMultiply{};
}

ExpressionRename* ExprMultiply::differentiate(const int variable) const
{
	throw 3;
}

expr_type ExprMultiply::get_type() const
{
	return EXPRESSION_TYPE_MULTIPLICATION;
}

ExpressionRename* ExprMultiply::simplify(const SimplificationRules& rules)
{
	if (children.size() == 1)
		return children.front()->clone();

	//		if (children.size() == 0)
	//			return none();
	ExprParent::simplify(rules);
	ExprParent::collapse();

	const auto end = children.end();
	auto it = children.begin();
	while (it != end)
	{
		ExpressionRename *child;
		switch ((*it)->get_type())
		{
		case EXPRESSION_TYPE_ZERO:
			return new ExprZero{};
		case EXPRESSION_TYPE_ONE:
			child = (*it);
			children.erase(it++);
			delete child;
			break;
		default:
			++it;
		}
	}
	return this;
}

void ExprMultiply::multiply(ExpressionRename* factor)
{
	children.push_back(factor);
}

ExpressionRename* ExprMultiply::evaluate(
		const Dictionary& dictionary) const
{
	ExprMultiply* multiplication = (ExprMultiply *) ExprParent::evaluate(dictionary);

	bool removed = false;
	double value = 1.0;
	const auto end = multiplication->children.end();
	auto it = multiplication->children.begin();

	while (it != end)
	{
		if ((*it)->get_type() != EXPRESSION_TYPE_VALUE)
		{
			it++;
			continue;
		}

		ExprValue *valexpr = (ExprValue *) (*it);
		removed = true;
		multiplication->children.erase(it++);
		value *= valexpr->get_value();
		delete valexpr;
	}

	if (removed)
	{
		if (multiplication->children.empty())
			return new ExprValue { value };

		multiplication->children.push_front(new ExprValue { value });
	}

	return multiplication;
}
