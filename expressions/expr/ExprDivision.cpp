/*
 * ExprDivision.cpp
 *
 *  Created on: Apr 3, 2016
 *      Author: default
 */

#include "ExprDivision.h"

#include "ExprMultiply.h"
#include "ExprPower.h"
#include "ExprValue.h"
#include "ExprSubtraction.h"

ExprDivision::ExprDivision(ExpressionRename* numerator,
		ExpressionRename* denominator) :
	numerator{numerator},
	denominator{denominator}
{
}

ExprDivision::~ExprDivision()
{
	delete numerator;
	delete denominator;
}

ExpressionRename* ExprDivision::clone() const
{
	return new ExprDivision{numerator->clone(), denominator->clone()};
}

ExpressionRename* ExprDivision::differentiate(const int variable) const
{
	if (denominator->get_type() == EXPRESSION_TYPE_VALUE)
	{
		return new ExprDivision { numerator->differentiate(variable), denominator->clone() };
	}

	return new ExprDivision
	{
		new ExprSubtraction{
			new ExprMultiply{numerator->differentiate(variable), denominator->clone()},
			new ExprMultiply{numerator->clone(), denominator->differentiate(variable)}
		},
		new ExprPower{denominator->clone(), new ExprValue{2}}
	};
}

expr_type ExprDivision::get_type() const
{
	return EXPRESSION_TYPE_DIVISION;
}

ExpressionRename* ExprDivision::simplify(const SimplificationRules& rules)
{
	return this;
}

ExpressionRename* ExprDivision::evaluate(const Dictionary& dictionary) const
{
	ExpressionRename *top = numerator->evaluate(dictionary);
	ExpressionRename *bottom = denominator->evaluate(dictionary);

	if (top->get_type() == EXPRESSION_TYPE_VALUE && bottom->get_type() == EXPRESSION_TYPE_VALUE)
	{
		double val = ((ExprValue *)top)->get_value() / ((ExprValue *)bottom)->get_value();
		delete top;
		delete bottom;
		return new ExprValue{ val };
	}

	return new ExprDivision { top, bottom };
}

void ExprDivision::print(std::ostream& out, int indentation,
		const ExpressionOutputFlags& flags) const
{
	out << "(";
	numerator->print(out, indentation+1, flags);
	out << ")/(";
	denominator->print(out, indentation+1, flags);
	out << ")";
}

bool ExprDivision::contains_variable(int variable) const
{
	return numerator->contains_variable(variable) || denominator->contains_variable(variable);
}
