/*
 * ExprDivision.h
 *
 *  Created on: Apr 3, 2016
 *      Author: default
 */

#ifndef EXPR_EXPRDIVISION_H_
#define EXPR_EXPRDIVISION_H_

#include "ExprParent.h"

class ExprDivision: public ExpressionRename
{
private:
	ExpressionRename *numerator;
	ExpressionRename *denominator;
public:
	ExprDivision(ExpressionRename *numerator, ExpressionRename *denominator);
	virtual ~ExprDivision();

	ExpressionRename* clone() const;
	ExpressionRename* differentiate(const int variable) const;
	expr_type get_type() const;
	ExpressionRename* simplify(const SimplificationRules& rules);
	ExpressionRename* evaluate(const Dictionary& dictionary) const;
	void print(std::ostream& out, int indentation, const ExpressionOutputFlags& flags = ExpressionOutputFlags{}) const;
	bool contains_variable(int variable) const;

};

#endif /* EXPR_EXPRDIVISION_H_ */