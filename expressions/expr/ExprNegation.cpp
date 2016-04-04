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
	return this;
}

ExpressionRename* ExprNegation::evaluate(const Dictionary& dictionary) const
{
	ExpressionRename *evaluated = child->evaluate(dictionary);
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

bool ExprNegation::contains_variable(int variable) const
{
	return child->contains_variable(variable);
}
