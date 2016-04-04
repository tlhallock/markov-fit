/*
 * ExprZero.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#include "ExprZero.h"

#include "ExprValue.h"

ExprZero::ExprZero()
{
}

ExprZero::~ExprZero()
{
}

ExpressionRename* ExprZero::clone() const
{
	return new ExprZero { };
}

ExpressionRename* ExprZero::differentiate(const int variable) const
{
	return clone();
}

ExpressionRename* ExprZero::evaluate(const Dictionary& dictionary) const
{
	return new ExprValue { 0 };
}

expr_type ExprZero::get_type() const
{
	return EXPRESSION_TYPE_ZERO;
}

void ExprZero::print(std::ostream& out, int indentation,
		const ExpressionOutputFlags& flags) const
{
	for (int i = 0; i < indentation; i++)
		out << '\t';
	out << '0' << '\n';
}

bool ExprZero::contains_variable(int variable) const
{
	return false;
}
