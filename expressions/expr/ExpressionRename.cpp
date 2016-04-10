/*
 * ExpressionRename.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#include "ExpressionRename.h"

#include "ExprMatrix.h"
#include "ExprOne.h"
#include "ExprZero.h"
#include "ExprValue.h"

ExpressionRename::ExpressionRename()
{
}

ExpressionRename::~ExpressionRename()
{
}


/**
 * Simplifies the expression.
 * The old expression should no longer be used. (It has been garbage collected.)
 */
ExpressionRename* expr_simplify(ExpressionRename* rename, const SimplificationRules& rules)
{
	while (true)
	{
		if (rename == nullptr)
		{
			std::cout << "Why null?" << std::endl;
			throw 1;
		}

//		std::cout << "Simplifying " << std::endl;
//		rename->print(std::cout, 0);
//		std::cout << std::endl;

		if (rename->get_type() == EXPRESSION_TYPE_MATRIX)
		{
			ExprMatrix *matrix = (ExprMatrix *) rename;
			if (matrix->get_m() == 1 && matrix->get_n() == 1)
			{
				rename = matrix->to_expr();
				delete matrix;
			}
		}
		if (rename->get_type() == EXPRESSION_TYPE_VALUE)
		{
			double val = ((ExprValue*) rename)->get_value();
			if (val == 0.0)
			{
				delete rename;
				rename = new ExprZero{};
			}
			else if (val == 1)
			{
				delete rename;
				rename = new ExprOne{};
			}
		}

		ExpressionRename* simplified = rename->simplify(rules);
		if (simplified == rename)
			return rename;

		delete rename;
		rename = simplified;
	}
}
