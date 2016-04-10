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
#include "ExprMatrix.h"

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

	int m, n; get_resulting_dimensions(m, n);
	if (m > 1 || n > 1)
	{
		SimplificationRules rules { true, true };
		ExpressionRename *rename = expr_simplify(clone(), rules);
		ExpressionRename *returnValue = rename->differentiate(variable);
		delete rename;
		return returnValue;
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
		return returnValue;
	}

	if (power->get_type() == EXPRESSION_TYPE_ZERO)
	{
		if (base->get_type() == EXPRESSION_TYPE_MATRIX)
		{
			ExprMatrix *matrix = (ExprMatrix*) base;
			int m = matrix->get_m();
			if (matrix->get_n() != m)
			{
				throw 1;
			}
			return create_identity(m);
		}
		return new ExprOne{};
	}

	if (base->get_type() == EXPRESSION_TYPE_ZERO)
	{
		ExpressionRename *returnValue = base;
		base = nullptr;
		return returnValue;
	}

	if (base->get_type() == EXPRESSION_TYPE_MATRIX && rules.simplify_exponentian && rules.simplify_matrix_multiplication)
	{
		if (power->get_type() != EXPRESSION_TYPE_VALUE)
		{
			std::cout << "Unable to simplify not values." << std::endl;
			throw 1;
		}
		int p = (int) ((ExprValue *) power)->get_value(); // Not necessarily integer...

		ExprMultiply *multiply = new ExprMultiply{};
		for (int i=0;i<p; i++)
			multiply->multiply(base->clone());
		return expr_simplify(multiply, rules);
	}

	return this;
}

ExpressionRename* ExprPower::substitute(const Dictionary& dictionary) const
{
	ExpressionRename *p = power->substitute(dictionary);
	ExpressionRename *b = base->substitute(dictionary);

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

Result* ExprPower::evaluate() const
{
	Result *b =  base->evaluate();
	Result *p = power->evaluate();
	if (b->is_scalar() && p->is_scalar())
	{
		b->set(0, 0, std::pow(b->value(0,0), p->value(0, 0)));
		delete p;
		return b;
	}

	if (!p->is_scalar())
		throw 1;

	double d = p->value(0, 0); // TODO
	delete p;

	int n = b->rows();
	if (n != b->cols())
		throw 1;

	Result *tmp = new Result { b };
	Result *tmp2 = new Result { b->rows(), b->cols() };

	// Dumb...
	for (int t = 1; t < d; t++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				double val = 0;

				for (int k = 0; k < n; k++)
					val += b->value(i, k)
							* tmp->value(k, j);

				tmp2->set(i, j, val);
			}
		}

		(*b) = tmp2;
	}

	delete tmp;
	delete tmp2;

	return b;
}

bool ExprPower::contains_variable(int variable) const
{
	return base->contains_variable(variable) || power->contains_variable(variable);
}
