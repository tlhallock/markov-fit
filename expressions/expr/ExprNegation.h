/*
 * ExprNegation.h
 *
 *  Created on: Apr 3, 2016
 *      Author: default
 */

#ifndef EXPR_EXPRNEGATION_H_
#define EXPR_EXPRNEGATION_H_

#include "ExpressionRename.h"

class ExprNegation : public ExpressionRename
{
	ExpressionRename *child;
public:
	ExprNegation(ExpressionRename *child);
	virtual ~ExprNegation();


	ExpressionRename* clone() const;
	ExpressionRename* differentiate(const int variable) const;
	expr_type get_type() const;
	ExpressionRename* simplify(const SimplificationRules& rules);
	ExpressionRename* substitute(const Dictionary& dictionary) const;
	Result* evaluate() const;
	void print(std::ostream& out, int indentation, const ExpressionOutputFlags& flags = ExpressionOutputFlags{}) const;
	bool contains_variable(int variable) const;

	void get_resulting_dimensions(int& m, int& n) const;
};

#endif /* EXPR_EXPRNEGATION_H_ */
