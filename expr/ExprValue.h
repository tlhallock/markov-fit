/*
 * ExprValue.h
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#ifndef EXPR_EXPRVALUE_H_
#define EXPR_EXPRVALUE_H_

#include "ExpressionRename.h"
#include "ExprZero.h"

class ExprValue: public ExpressionRename {
private:
	double value;
public:
	ExprValue(double value) : value{value} {}
	~ExprValue() {}

	ExpressionRename* clone() { return new ExprValue{value}; }
	ExpressionRename* differentiate(const int variable) { return new ExprZero{} };
	expr_type get_type() { return EXPRESSION_TYPE_VALUE; }

	virtual ExpressionRename* simplify()
	{
		if (value == 0)
			return new ExprZero{};
		if (value == 1)
			return new ExprOne{};
		return this;
	};
	virtual ExpressionRename* evaluate(const Dictionary& dictionary) { return clone(); };

	virtual void print(std::ostream& out, int indentation)
	{
		for (int i=0;i<indentation;i++)
			out << '\t';
		out << value << '\n';
	}
};

#endif /* EXPR_EXPRVALUE_H_ */
