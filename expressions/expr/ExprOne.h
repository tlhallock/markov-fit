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

	Result* evaluate() const;
	ExpressionRename* substitute(const Dictionary& dictionary) const;
	bool contains_variable(int variable) const;

	void get_resulting_dimensions(int& m, int& n) const;
};


#endif /* EXPR_EXPRONE_H_ */
