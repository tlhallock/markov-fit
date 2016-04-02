/*
 * ExprOne.h
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#ifndef EXPR_EXPRONE_H_
#define EXPR_EXPRONE_H_

#include "ExpressionRename.h"

class ExprOne  : public ExpressionRename {
public:
	ExprOne();
	virtual ~ExprOne();


	ExpressionRename* clone() const;
	ExpressionRename* differentiate(const int variable) const;
	expr_type get_type() const;

	void print(std::ostream& out, int indentation,
			const ExpressionOutputFlags& flags) const;

	ExpressionRename* evaluate(const Dictionary& dictionary) const;
};


#endif /* EXPR_EXPRONE_H_ */