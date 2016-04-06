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

ExpressionRename* ExprZero::substitute(const Dictionary& dictionary) const
{
	return new ExprValue { 0 };
}


Result* ExprZero::evaluate() const
{
	Result *returnValue = new Result{1, 1};
	returnValue->set(0, 0, 0);
	return returnValue;
}


expr_type ExprZero::get_type() const
{
	return EXPRESSION_TYPE_ZERO;
}

void ExprZero::print(std::ostream& out, int indentation,
		const ExpressionOutputFlags& flags) const
{
	if (flags.indent)
		for (int i = 0; i < indentation; i++)
			out << '\t';
	out << '0';
	if (flags.indent)
		out << '\n';
}

bool ExprZero::contains_variable(int variable) const
{
	return false;
}
