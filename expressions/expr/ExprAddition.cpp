/*
 * ExprAddition.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: default
 */

#include "ExprAddition.h"

ExprAddition::ExprAddition(ExpressionRename* l, ExpressionRename* r)
{
	children.push_back(l);
	children.push_back(r);
}

ExprAddition::ExprAddition()
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

	const auto end = children.end();
	auto it = children.begin();
	while (it != end)
	{
		ExpressionRename *child;
		switch ((*it)->get_type())
		{
		case EXPRESSION_TYPE_ZERO:
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

ExprParent* ExprAddition::newOne() const
{
	return new ExprAddition{};
}

ExpressionRename* ExprAddition::evaluate(const Dictionary& dictionary) const
{
	bool is_matrix = children.front()->get_type() == EXPRESSION_TYPE_MATRIX;
	if (is_matrix)
	{
		int m = ((ExprMatrix *)children.front())->get_m();
		int n = ((ExprMatrix *)children.front())->get_n();

		const auto end = children.end();
		for (auto it = children.begin(); it != end; ++it)
		{
			if ((*it)->get_type() != EXPRESSION_TYPE_MATRIX)
			{
				throw 1;
			}

			ExprMatrix *mat = (ExprMatrix *) (*it);
			if (mat->get_m() != m || mat->get_n() != n)
			{
				throw 2;
			}
		}
	}

	if (is_matrix)
	{
	}
	else
	{
		const auto end = children.end();
		for (auto it = children.begin(); it != end; ++it)
		{
		}
	}

	return nullptr;
}
