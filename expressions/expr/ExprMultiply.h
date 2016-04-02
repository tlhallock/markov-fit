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

public:
	ExprMultiply(ExpressionRename* l, ExpressionRename* r);
	virtual ~ExprMultiply();

	ExpressionRename* clone() const;

	ExpressionRename* differentiate(const int variable) const;

	expr_type get_type() const;

	ExpressionRename* simplify(const SimplificationRules& rules);

	ExpressionRename* evaluate(const Dictionary& dictionary) const;
};

#endif /* EXPR_EXPRMULTIPLY_H_ */