/*
 * ExprZero.h
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#ifndef EXPR_EXPRZERO_H_
#define EXPR_EXPRZERO_H_

#include "ExpressionRename.h"

class ExprZero : public ExpressionRename {
public:
	ExprZero() {}
	virtual ~ExprZero() {}

	virtual ExpressionRename* clone() { return new ExprZero(); }
	virtual ExpressionRename* differentiate(const int variable) { return new ExprZero{}; }
	virtual expr_type get_type() { return EXPRESSION_TYPE_ZERO; }

	virtual void print(std::ostream& out, int indentation)
	{
		for (int i=0;i<indentation;i++)
			out << '\t';
		out << '0' << '\n';
	}
};

#endif /* EXPR_EXPRZERO_H_ */
