/*
 * ExprNegation.cpp
 *
 *  Created on: Apr 3, 2016
 *      Author: default
 */

#include "ExprNegation.h"

#include "ExprValue.h"


ExprNegation::ExprNegation(ExpressionRename* child) :
	child{child}
{
}

ExprNegation::~ExprNegation()
{
	delete child;
}

ExpressionRename* ExprNegation::clone() const
{
	return new ExprNegation{child->clone()};
}

ExpressionRename* ExprNegation::differentiate(const int variable) const
{
	return new ExprNegation{child->differentiate(variable)};
}

expr_type ExprNegation::get_type() const
{
	return EXPRESSION_TYPE_NEGATION;
}

ExpressionRename* ExprNegation::simplify(const SimplificationRules& rules)
{
	child = expr_simplify(child, rules);
	if (child->get_type() == EXPRESSION_TYPE_NEGATION)
	{
		ExpressionRename *gchild = ((ExprNegation *) child)->child;
		((ExprNegation *) child)->child = nullptr;
		return gchild;
	}
	else if (child->get_type() == EXPRESSION_TYPE_ADDITION)
	{
		// TODO
	}
	else if (child->get_type() == EXPRESSION_TYPE_SUBTRACTION)
	{
		// TODO
	}
	return this;
}

ExpressionRename* ExprNegation::substitute(const Dictionary& dictionary) const
{
	ExpressionRename *evaluated = child->substitute(dictionary);
	if (evaluated->get_type() == EXPRESSION_TYPE_VALUE)
		((ExprValue *) evaluated)->negate();
	return evaluated;
}

void ExprNegation::print(std::ostream& out, int indentation,
		const ExpressionOutputFlags& flags) const
{
	out << "-(";
	child->print(out, indentation+1, flags);
	out << ")";
}

Result* ExprNegation::evaluate() const
{
	Result *returnValue = child->evaluate();
	for (int i=0;i<returnValue->rows();i++)
		for (int j=0;j<returnValue->cols(); j++)
			returnValue->set(i, j, -returnValue->value(i, j));
	return returnValue;
}

bool ExprNegation::contains_variable(int variable) const
{
	return child->contains_variable(variable);
}
