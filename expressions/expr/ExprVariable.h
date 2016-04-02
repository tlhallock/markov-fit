/*
 * ExprVariable.h
 *
 *  Created on: Apr 2, 2016
 *      Author: thallock
 */

#ifndef EXPR_EXPRVARIABLE_H_
#define EXPR_EXPRVARIABLE_H_

#include "ExpressionRename.h"

class ExprVariable : public ExpressionRename {
	int index;
public:
	ExprVariable(int index);
	virtual ~ExprVariable();


	ExpressionRename* clone() const;
	ExpressionRename* differentiate(const int variable) const;

	expr_type get_type() const;

	ExpressionRename* simplify(const SimplificationRules& rules);
	;
	ExpressionRename* evaluate(const Dictionary& dictionary) const;
	void print(std::ostream& out, int indentation,
			const ExpressionOutputFlags& flags) const;
};


#endif /* EXPR_EXPRVARIABLE_H_ */
