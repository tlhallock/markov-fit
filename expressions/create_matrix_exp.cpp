/*
 * create_matrix_exp.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: default
 */

#include "create_matrix_exp.h"

//#include "ExprMatrix.h"
//#include "ExprAddition.h"
//#include "ExprPower.h"
//#include "ExprMultiply.h"

#include "expressions.h"

ExpressionRename *create_matrix_exponential(int nrows, int order)
{
	if (order < 0)
		return nullptr;

	ExprAddition *addition = new ExprAddition{};

	ExprMatrix *mat = create_identity(nrows);
	addition->add(mat);

	double prod = 1;

	for(int i=1;i<=order;i++)
		addition->add(
			new ExprMultiply {
				new ExprValue{prod /= i},
				new ExprPower {
					create_variable_matrix(nrows),
							new ExprValue{(double) i}}});

	return addition;
}
