/*
 * ExprAddition.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: default
 */

#include "ExprAddition.h"

#include "../util.h"

#include "ExprMatrix.h"
#include "ExprValue.h"

#include <algorithm>

ExprAddition::ExprAddition(ExpressionRename* l, ExpressionRename* r) :
	ExprParent{'+'}
{
	children.push_back(l);
	children.push_back(r);
}

ExprAddition::ExprAddition() :
	ExprParent{'+'}
{
}

ExprAddition::~ExprAddition()
{
	const auto end = children.end();
	for (auto it = children.begin(); it != end; ++it)
	{
		delete *it;
	}
}

ExpressionRename* ExprAddition::differentiate(const int variable) const
{
	ExprAddition *add = new ExprAddition{};

	const auto end = children.end();
	for (auto it = children.begin(); it != end; ++it)
	{
		add->children.push_back((*it)->differentiate(variable));
	}

	return add;
}

expr_type ExprAddition::get_type() const
{
	return EXPRESSION_TYPE_ADDITION;
}

ExpressionRename* ExprAddition::simplify(const SimplificationRules& rules)
{
	if (children.size() == 1)
		return children.front()->clone();

	ExprParent::simplify(rules);
	ExprParent::collapse();

	bool is_matrix = children.front()->get_type() == EXPRESSION_TYPE_MATRIX;
	if (is_matrix)
	{
		return expr_matrix_simplify_sum(children);
	}

	const auto end = children.end();
	auto it = children.begin();
	while (it != end)
	{
		ExpressionRename *child;
		ExprMatrix *mat;
		switch ((*it)->get_type())
		{
		case EXPRESSION_TYPE_ZERO:
			child = (*it);
			children.erase(it++);
			delete child;
			break;
		case EXPRESSION_TYPE_MATRIX:
			mat = (ExprMatrix *)(*it);
			children.erase(it++);
			children.insert(it, expr_simplify(mat->to_expr()));
			delete mat;
			break;
		default:
			++it;
		}
	}
	return this;
}

ExprParent* ExprAddition::newOne() const
{
	return new ExprAddition{};
}

void ExprAddition::add(ExpressionRename* expr)
{
	children.push_back(expr);
}

bool expr_add_is_value(const ExpressionRename* expr)
{
	return expr->get_type() == EXPRESSION_TYPE_VALUE;
}

ExpressionRename* ExprAddition::evaluate(const Dictionary& dictionary) const
{
	ExprAddition* addition = (ExprAddition *) ExprParent::evaluate(dictionary);

	bool removed = false;
	double value = 0.0;
	const auto end = addition->children.end();
	auto it = addition->children.begin();

	while (it != end)
	{
		if ((*it)->get_type() != EXPRESSION_TYPE_VALUE)
		{
			it++;
			continue;
		}

		ExprValue *valexpr = (ExprValue *) (*it);
		removed = true;
		addition->children.erase(it++);
		value += valexpr->get_value();
		delete valexpr;
	}

	if (removed)
	{
		if (addition->children.empty())
			return new ExprValue { value };

		addition->children.push_front(new ExprValue { value });
	}

	return addition;
}









//
//
//move_if(children, std::back_insert_iterator<std::list<int>>{list}, expr_add_is_value);
//
//
////
////	children.remove_if(expr_add_is_value);
////
////	remove_copy_if
//
//const auto end = children.end();
//auto it = children.begin();
//while (it != end)
//{
//	ExpressionRename *child;
//	ExprMatrix *mat;
//	switch ((*it)->get_type())
//	{
//	case EXPRESSION_TYPE_ZERO:
//		child = (*it);
//		children.erase(it++);
//		delete child;
//		break;
//	case EXPRESSION_TYPE_MATRIX:
//		mat = (ExprMatrix *)(*it);
//		children.erase(it++);
//		children.insert(it, expr_simplify(mat->to_expr()));
//		delete mat;
//		break;
//	default:
//		++it;
//	}
//}
