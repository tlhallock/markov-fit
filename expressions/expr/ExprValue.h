/*
 * ExprValue.h
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#ifndef EXPR_EXPRVALUE_H_
#define EXPR_EXPRVALUE_H_

#include "ExpressionRename.h"

class ExprValue: public ExpressionRename {
private:
	double value;
public:
	ExprValue(double value);
	~ExprValue();

	ExpressionRename* clone() const { return new ExprValue{value}; }
	ExpressionRename* differentiate(const int variable) const;

	expr_type get_type() const;

	virtual ExpressionRename* simplify(const SimplificationRules& rules);

	virtual ExpressionRename* evaluate(const Dictionary& dictionary) const;


	virtual void print(std::ostream& out, int indentation,
			const ExpressionOutputFlags& flags) const;
};

#endif /* EXPR_EXPRVALUE_H_ */
