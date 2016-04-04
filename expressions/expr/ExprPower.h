/*
 * ExprPower.h
 *
 *  Created on: Apr 3, 2016
 *      Author: default
 */

#ifndef EXPR_EXPRPOWER_H_
#define EXPR_EXPRPOWER_H_

#include "ExpressionRename.h"

class ExprPower : public ExpressionRename
{
	ExpressionRename *base;
	ExpressionRename *power;
public:
	ExprPower(ExpressionRename *base, ExpressionRename *power);
	virtual ~ExprPower();

	ExpressionRename* clone() const;
	ExpressionRename* differentiate(const int variable) const;
	expr_type get_type() const;
	ExpressionRename* simplify(const SimplificationRules& rules);
	ExpressionRename* evaluate(const Dictionary& dictionary) const;
	void print(std::ostream& out, int indentation, const ExpressionOutputFlags& flags = ExpressionOutputFlags{}) const;
	bool contains_variable(int variable) const;
};



#endif /* EXPR_EXPRPOWER_H_ */
