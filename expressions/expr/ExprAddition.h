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
private:
	ExprAddition();

protected:
	ExprParent *newOne() const;

public:
	ExprAddition(ExpressionRename* l, ExpressionRename* r);
	virtual ~ExprAddition();

	ExpressionRename* differentiate(const int variable) const;
	expr_type get_type() const;
	ExpressionRename* simplify(const SimplificationRules& rules);
	ExpressionRename* evaluate(const Dictionary& dictionary) const;
};

#endif /* EXPR_EXPRADDITION_H_ */
