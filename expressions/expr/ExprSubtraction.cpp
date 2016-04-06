/*
 * ExprSubtraction.cpp
 *
 *  Created on: Apr 3, 2016
 *      Author: default
 */

#include "ExprSubtraction.h"

#include "ExprZero.h"

ExprSubtraction::ExprSubtraction() : ExprParent{'-'} {}

ExprSubtraction::ExprSubtraction(ExpressionRename* left,
		ExpressionRename* right) :
	ExprParent{'-'}
{
}

ExprSubtraction::~ExprSubtraction() {}

ExprParent* ExprSubtraction::newOne() const
{
	return new ExprSubtraction{};
}

ExpressionRename* ExprSubtraction::differentiate(const int variable) const
{
	ExprSubtraction *derivative = new ExprSubtraction{};

	const auto end = children.end();
	for (auto it = children.begin(); it != end; ++it)
	{
		derivative->children.push_back((*it)->differentiate(variable));
	}

	return derivative;
}

expr_type ExprSubtraction::get_type() const
{
	return EXPRESSION_TYPE_SUBTRACTION;
}

ExpressionRename* ExprSubtraction::simplify(const SimplificationRules& rules)
{
//	if (children.size() == 0)
//	{
//		return new ExprZero{};
//	}
	return this;
}

Result* ExprSubtraction::evaluate() const
{
	Result *returnValue = nullptr;
	int rows = -1;
	int cols = -1;

	const auto end = children.end();
	for (auto it = children.begin(); it != end; ++it)
	{
		Result *next = (*it)->evaluate();

		if (returnValue == nullptr)
		{
			returnValue = next;
			rows = returnValue->rows();
			cols = returnValue->cols();
		}
		else
		{
			if (rows != next->rows() || cols != next->cols())
				throw -1;
			for (int i=0;i<rows;i++)
				for (int j=0;j<cols;j++)
					returnValue->set(i, j, returnValue->value(i, j) - next->value(i, j));
			delete next;
		}

	}

	return returnValue;

}
