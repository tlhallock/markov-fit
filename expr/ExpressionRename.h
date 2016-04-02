/*
 * ExpressionRename.h
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#ifndef EXPR_EXPRESSIONRENAME_H_
#define EXPR_EXPRESSIONRENAME_H_

#include <vector>
#include <iostream>

#include "Dictionary.h"


typedef enum
{
	EXPRESSION_TYPE_ZERO,
	EXPRESSION_TYPE_ONE,

	EXPRESSION_TYPE_VALUE,
	EXPRESSION_TYPE_VARIABLE,

	EXPRESSION_TYPE_ADDITION,
	EXPRESSION_TYPE_SUBTRACTION,
	EXPRESSION_TYPE_MULTIPLICATION,
	EXPRESSION_TYPE_DIVISION,

	EXPRESSION_TYPE_MATRIX,

	EXPRESSION_TYPE_ERROR,
} expr_type;

class ExpressionRename {
public:
	ExpressionRename();
	virtual ~ExpressionRename();

	virtual ExpressionRename* clone() = 0;
	virtual ExpressionRename* differentiate(const int variable) = 0;
	virtual expr_type get_type() = 0;

	virtual ExpressionRename* simplify() { return this; };
	virtual ExpressionRename* evaluate(const Dictionary& dictionary) { return clone(); };
	virtual void print(std::ostream& out, int indentation) = 0;

};

ExpressionRename *expr_simplify(ExpressionRename *rename)
{
	while (true)
	{
		ExpressionRename *simplified = rename->simplify();
		if (simplified == rename)
			return rename;
		delete rename;
		rename = simplified;
	}
}





#endif /* EXPR_EXPRESSIONRENAME_H_ */
