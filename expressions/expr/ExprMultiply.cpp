/*
 * ExprMultiply.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#include "ExprMultiply.h"

#include "ExprZero.h"
//#include "ExprOne.h"


ExprMultiply::ExprMultiply(ExpressionRename* l, ExpressionRename* r) :
		ExprParent { '*' }
{
	children.push_back(l);
	children.push_back(r);
}

ExprMultiply::~ExprMultiply()
{
}

ExpressionRename* ExprMultiply::clone() const
{
	throw 2;
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
	const auto end = children.end();
	auto it = children.begin();
	while (it != end)
	{
		expr_type t = (*it)->get_type();
//		if (t == EXPRESSION_TYPE_MULTIPLICATION)
//		{
//			ExprMultiply* child = (ExprMultiply*) ((*it));
//			children.splice(it, child->get_children());
//			++it;
//			children.erase(it);
//			delete child;
//		} else
			if (t == EXPRESSION_TYPE_ZERO)
		{
			return new ExprZero { };
		} else if (t == EXPRESSION_TYPE_ONE)
		{
			ExprMultiply* child = (ExprMultiply*) ((*it));
			++it;
			children.erase(it);
			delete child;
		} else
		{
			++it;
		}
	}
	return this;
}

ExpressionRename* ExprMultiply::evaluate(
		const Dictionary& dictionary) const
{
	ExprParent::evaluate(dictionary);
}
