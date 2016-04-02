/*
 * ExprVariable.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: thallock
 */

#include "ExprVariable.h"

#include "ExprZero.h"
#include "ExprOne.h"

ExprVariable::ExprVariable(int index) :
		index { index }
{
}

ExprVariable::~ExprVariable()
{
}

ExpressionRename* ExprVariable::clone() const
{
	return new ExprVariable { index };
}

ExpressionRename* ExprVariable::differentiate(const int variable) const
{
	if (index == variable)
		return new ExprOne { };

	return new ExprZero { };
}

expr_type ExprVariable::get_type() const
{
	return EXPRESSION_TYPE_VARIABLE;
}

ExpressionRename* ExprVariable::simplify(const SimplificationRules& rules)
{
	return this;
}

ExpressionRename* ExprVariable::evaluate(
		const Dictionary& dictionary) const
{
	ExpressionRename* expr = dictionary.get(index);
	return clone();
}

void ExprVariable::print(std::ostream& out, int indentation,
		const ExpressionOutputFlags& flags) const
{
	if (flags.indent)
		for (int i = 0; i < indentation; i++)
			out << '\t';

	out << "variable[" << index << ']';

	if (flags.indent)
		out << '\n';
}
