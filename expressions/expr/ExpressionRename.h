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
#include "ExpressionOutputFlags.h"
#include "SimplificationRules.h"

typedef enum
{
	EXPRESSION_TYPE_ZERO,
	EXPRESSION_TYPE_ONE,

	EXPRESSION_TYPE_VALUE,
	EXPRESSION_TYPE_VARIABLE,

	EXPRESSION_TYPE_NEGATION,
	EXPRESSION_TYPE_POWER,

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

	/**
	 * Returns a copy of this expression.
	 * This expression is still valid.
	 */
	virtual ExpressionRename* clone() const = 0;

	/**
	 * Returns a differentiated copy of this expression.
	 * This expression is still valid.
	 */
	virtual ExpressionRename* differentiate(const int variable) const = 0;

	/**
	 * Returns the type of this expression.
	 */
	virtual expr_type get_type() const = 0;

	/**
	 * Returns a simplified version of this expression.
	 * If this is returned, then the expression is still valid.
	 * Otherwise, this expression should be deleted.
	 */
	virtual ExpressionRename* simplify(const SimplificationRules& rules) { return this; };

	/**
	 * Returns a new expression that results from evaluating this expression with the given dictionary.
	 * The previous expression is still valid.
	 */
	virtual ExpressionRename* evaluate(const Dictionary& dictionary) const = 0;

	/**
	 * Prints the expression to the specified output stream.
	 */
	virtual void print(std::ostream& out, int indentation, const ExpressionOutputFlags& flags = ExpressionOutputFlags{}) const = 0;

	virtual bool contains_variable(int variable) const = 0;
};

/**
 * Simplifies the expression.
 * The old expression should no longer be used. (It has been garbage collected.)
 */
ExpressionRename* expr_simplify(ExpressionRename* rename, const SimplificationRules& rules = SimplificationRules{});





#endif /* EXPR_EXPRESSIONRENAME_H_ */
