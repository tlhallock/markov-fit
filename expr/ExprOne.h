/*
 * ExprOne.h
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#ifndef EXPR_EXPRONE_H_
#define EXPR_EXPRONE_H_

#include "ExpressionRename.h"
#include "ExprZero.h"

class ExprOne  : public ExpressionRename {
public:
	ExprOne() {}
	virtual ~ExprOne() {}


	virtual ExpressionRename* clone() { return new ExprOne(); }
	virtual ExpressionRename* differentiate(const int variable) { return new ExprZero{}; }
	virtual expr_type get_type() { return EXPRESSION_TYPE_ONE; }

	virtual void print(std::ostream& out, int indentation)
	{
		for (int i=0;i<indentation;i++)
			out << '\t';
		out << '1' << '\n';
	}

	virtual ExpressionRename* simplify() { return this; };
	virtual ExpressionRename* evaluate(const Dictionary& dictionary) { return clone(); };
};

#endif /* EXPR_EXPRONE_H_ */
