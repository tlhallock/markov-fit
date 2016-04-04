/*
 * ExprPower.cpp
 *
 *  Created on: Apr 3, 2016
 *      Author: default
 */

#include "ExprPower.h"
#include "ExprMultiply.h"
#include "ExprOne.h"
#include "ExprSubtraction.h"
#include "ExprValue.h"

#include <cmath>

ExprPower::ExprPower(ExpressionRename* base, ExpressionRename* power) :
	base{base},
	power{power}
{
}

ExprPower::~ExprPower()
{
	delete base;
	delete power;
}

ExpressionRename* ExprPower::clone() const
{
	return new ExprPower {base->clone(), power->clone()};
}

ExpressionRename* ExprPower::differentiate(const int variable) const
{
	if (power->contains_variable(variable))
	{
		throw 1;
	}

	ExprMultiply * mult = new ExprMultiply{};
	mult->multiply(power->clone());
	mult->multiply(new ExprPower{base->clone(), new ExprSubtraction{power->clone(), new ExprOne{}}});
	mult->multiply(base->differentiate(variable));

	return mult;
}

expr_type ExprPower::get_type() const
{
	return EXPRESSION_TYPE_POWER;
}

ExpressionRename* ExprPower::simplify(const SimplificationRules& rules)
{
	power = expr_simplify(power);
	base  = expr_simplify(base);

	if (power->get_type() == EXPRESSION_TYPE_ONE)
	{
		ExpressionRename *returnValue = base;
		base = nullptr;
		return base;
	}

	if (power->get_type() == EXPRESSION_TYPE_ZERO)
	{
		return new ExprOne{};
	}

	return this;
}

ExpressionRename* ExprPower::evaluate(const Dictionary& dictionary) const
{
	ExpressionRename *p = power->evaluate(dictionary);
	ExpressionRename *b = base->evaluate(dictionary);

	if (p->get_type() == EXPRESSION_TYPE_ONE)
	{
		delete p;
		return b;
	}
	if (p->get_type() == EXPRESSION_TYPE_ZERO)
	{
		delete p;
		delete b;
		return new ExprOne{};
	}
	if (p->get_type() == EXPRESSION_TYPE_VALUE && b->get_type() == EXPRESSION_TYPE_VALUE)
	{
		ExpressionRename *returnValue = new ExprValue{std::pow(((ExprValue *) b)->get_value(), ((ExprValue *)p)->get_value())};
		delete p;
		delete b;
		return returnValue;
	}

	return new ExprPower{b, p};
}

void ExprPower::print(std::ostream& out, int indentation,
		const ExpressionOutputFlags& flags) const
{
	out << "(";
	base->print(out, indentation+1, flags);
	out << ")^(";
	power->print(out, indentation+1, flags);
	out << ")";
}

bool ExprPower::contains_variable(int variable) const
{
	return base->contains_variable(variable) || power->contains_variable(variable);
}
