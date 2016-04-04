/*
 * ExprSubtraction.cpp
 *
 *  Created on: Apr 3, 2016
 *      Author: default
 */

#include "ExprSubtraction.h"

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
	return this;
}

ExpressionRename* ExprSubtraction::evaluate(const Dictionary& dictionary) const
{
	throw 1;
}
