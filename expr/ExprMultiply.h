/*
 * ExprMultiply.h
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#ifndef EXPR_EXPRMULTIPLY_H_
#define EXPR_EXPRMULTIPLY_H_

#include "ExprParent.h"

class ExprMultiply : public ExprParent {
public:
	ExprMultiply(ExpressionRename *l, ExpressionRename *r) : ExprParent{'+'}
	{
		children.push_back(l);
		children.push_back(r);
	}
	virtual ~ExprMultiply() {}



	virtual ExpressionRename* clone() {

	};
	virtual ExpressionRename* differentiate(const int variable) = 0;
	virtual expr_type get_type();

	virtual ExpressionRename* simplify()
	{
		if (children.size() == 1)
			return children.at(0)->clone();
//		if (children.size() == 0)
//			return none();


		int size = children.size();
		for (int i=0;i<size;i++)
		{
			children.at(i) = expr_simplify(children.at(i));
		}
	}

	virtual ExpressionRename* evaluate(const Dictionary& dictionary) { return clone(); };

};

inline expr_type ExprMultiply::get_type() {
	return EXPRESSION_TYPE_MULTIPLICATION;
}

#endif /* EXPR_EXPRMULTIPLY_H_ */
