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
	ExprZero();
	virtual ~ExprZero();

	ExpressionRename* clone() const;
	ExpressionRename* differentiate(const int variable) const;
	ExpressionRename* substitute(const Dictionary& dictionary) const;

	expr_type get_type() const;


	Result* evaluate() const;

	void print(std::ostream& out, int indentation,
			const ExpressionOutputFlags& flags) const;

	bool contains_variable(int variable) const;
};


#endif /* EXPR_EXPRZERO_H_ */
