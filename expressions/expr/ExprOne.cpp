/*
 * ExprOne.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#include "ExprOne.h"
#include "ExprZero.h"
#include "ExprValue.h"

ExprOne::ExprOne()
{
}

ExprOne::~ExprOne()
{
}

ExpressionRename* ExprOne::clone() const
{
	return new ExprOne { };
}

ExpressionRename* ExprOne::differentiate(const int variable) const
{
	return new ExprZero { };
}

expr_type ExprOne::get_type() const
{
	return EXPRESSION_TYPE_ONE;
}

void ExprOne::print(std::ostream& out, int indentation,
		const ExpressionOutputFlags& flags) const
{
	for (int i = 0; i < indentation; i++)
		out << '\t';
	out << '1' << '\n';
}

ExpressionRename* ExprOne::evaluate(const Dictionary& dictionary) const
{
	return new ExprValue { 1 };
}