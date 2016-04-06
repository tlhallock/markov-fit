/*
 * ExprMultiply.h
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#ifndef EXPR_EXPRMULTIPLY_H_
#define EXPR_EXPRMULTIPLY_H_

#include "ExprParent.h"

class ExprMultiply : public ExprParent {

protected:
	ExprParent* newOne() const;

public:
	ExprMultiply();
	ExprMultiply(ExpressionRename* l, ExpressionRename* r);
	virtual ~ExprMultiply();

	void multiply(ExpressionRename *factor);

	ExpressionRename* differentiate(const int variable) const;
	expr_type get_type() const;
	ExpressionRename* simplify(const SimplificationRules& rules);
	Result* evaluate() const;
};

#endif /* EXPR_EXPRMULTIPLY_H_ */
