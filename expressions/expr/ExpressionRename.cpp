/*
 * ExpressionRename.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#include "ExpressionRename.h"

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
		ExpressionRename* simplified = rename->simplify(rules);
		if (simplified == rename)
			return rename;

		delete rename;
		rename = simplified;
	}
}
