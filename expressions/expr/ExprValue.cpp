/*
 * ExprValue.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#include "ExprValue.h"

#include "ExprZero.h"
#include "ExprOne.h"


ExprValue::ExprValue(double value) :
		value { value }
{
}

ExprValue::~ExprValue()
{
}

ExpressionRename* ExprValue::differentiate(const int variable) const
{
	return new ExprZero { };
}

expr_type ExprValue::get_type() const
{
	return EXPRESSION_TYPE_VALUE;
}

ExpressionRename* ExprValue::simplify(const SimplificationRules& rules)
{
	if (value == 0)
		return new ExprZero{};

	if (value == 1)
		return new ExprOne{};

	return this;
}

ExpressionRename* ExprValue::evaluate(const Dictionary& dictionary) const
{
	return clone();
}

void ExprValue::print(std::ostream& out, int indentation,
		const ExpressionOutputFlags& flags) const
{
	if (flags.indent)
		for (int i = 0; i < indentation; i++)
			out << '\t';
	out << value;

	if (flags.indent)
		out << '\n';
}

void ExprValue::negate()
{
	value = -value;
}

bool ExprValue::contains_variable(int variable) const
{
	return false;
}
