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
	numerator = expr_simplify(numerator);
	denominator = expr_simplify(denominator);
	while (denominator->get_type() == EXPRESSION_TYPE_DIVISION)
	{
		ExprDivision *d = (ExprDivision *) denominator;
		numerator = expr_simplify(new ExprMultiply{numerator, d->denominator});
		denominator = d->numerator;
		d->numerator = nullptr;
		d->denominator = nullptr;
		delete d;
	}
	return this;
}

ExpressionRename* ExprDivision::substitute(const Dictionary& dictionary) const
{
	ExpressionRename *top = numerator->substitute(dictionary);
	ExpressionRename *bottom = denominator->substitute(dictionary);

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

void divide(Result *res, double val)
{
	int r = res->rows();
	int c = res->cols();
	for (int i=0;i<r;i++)
		for (int j=0;j<c;j++)
			res->set(i, j, res->value(i, j) / val);
}

Result* ExprDivision::evaluate() const
{
	Result *n = numerator->evaluate();
	Result *d = numerator->evaluate();
	if (n->is_scalar())
	{
		divide(d, n->value(0, 0));
		delete n;
		return d;
	}
	if (d->is_scalar())
	{
		divide(n, d->value(0, 0));
		delete d;
		return n;
	}

	throw 1;
}

bool ExprDivision::contains_variable(int variable) const
{
	return numerator->contains_variable(variable) || denominator->contains_variable(variable);
}

void ExprDivision::get_resulting_dimensions(int& m, int& n) const
{
	int m1, n1, m2, n2;
	denominator->get_resulting_dimensions(m1, n1);
	numerator->get_resulting_dimensions(m2, n2);

	if (m2 == 1 && n2 == 1)
	{
		m = m1; n = n1;
		return;
	}
	if (m1 == 1 && n1 == 1)
	{
		m = m2; n = n2;
		return;
	}
	throw 1;
}
