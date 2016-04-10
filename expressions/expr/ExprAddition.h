/*
 * ExprAddition.h
 *
 *  Created on: Apr 2, 2016
 *      Author: default
 */

#ifndef EXPR_EXPRADDITION_H_
#define EXPR_EXPRADDITION_H_

#include "ExprParent.h"

class ExprAddition: public ExprParent
{
protected:
	ExprParent *newOne() const;

public:
	ExprAddition();
	ExprAddition(ExpressionRename* l, ExpressionRename* r);
	virtual ~ExprAddition();

	/**
	 * Modifies the current expression to also have the new term at the end.
	 */
	void add(ExpressionRename *expr);

	ExpressionRename* differentiate(const int variable) const;
	expr_type get_type() const;
	ExpressionRename* simplify(const SimplificationRules& rules);
	Result* evaluate() const;

	void get_resulting_dimensions(int& m, int& n) const;
};

#endif /* EXPR_EXPRADDITION_H_ */
