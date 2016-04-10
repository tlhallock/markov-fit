/*
 * ExprSubtraction.h
 *
 *  Created on: Apr 3, 2016
 *      Author: default
 */

#ifndef EXPR_EXPRSUBTRACTION_H_
#define EXPR_EXPRSUBTRACTION_H_

#include "ExprParent.h"

class ExprSubtraction : public ExprParent
{
protected:
	ExprParent *newOne() const;
public:
	ExprSubtraction();
	ExprSubtraction(ExpressionRename *left, ExpressionRename *right);
	virtual ~ExprSubtraction();

	ExpressionRename* differentiate(const int variable) const;
	expr_type get_type() const;
	ExpressionRename* simplify(const SimplificationRules& rules);
	Result* evaluate() const;

	void get_resulting_dimensions(int& m, int& n) const;
};

#endif /* EXPR_EXPRSUBTRACTION_H_ */
