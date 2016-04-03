/*
 * ExprMatrix.h
 *
 *  Created on: Apr 2, 2016
 *      Author: default
 */

#ifndef EXPR_EXPRMATRIX_H_
#define EXPR_EXPRMATRIX_H_

#include "ExpressionRename.h"

class ExprMatrix : public ExpressionRename
{
private:
	int m, n;
	ExpressionRename **elems;

public:
	ExprMatrix(int m, int n);
	virtual ~ExprMatrix();

	int get_m() const { return m; }
	int get_n() const { return n; }

	ExpressionRename* get(int i, int j);
	void set(int i, int j, ExpressionRename *expr);
	ExpressionRename* multiply(const ExprMatrix* expr) const;

	ExpressionRename* clone() const;
	ExpressionRename* differentiate(const int variable) const;
	expr_type get_type() const;
	ExpressionRename* simplify(const SimplificationRules& rules);
	ExpressionRename* evaluate(const Dictionary& dictionary) const;
	void print(std::ostream& out, int indentation, const ExpressionOutputFlags& flags = ExpressionOutputFlags{}) const;
};

#endif /* EXPR_EXPRMATRIX_H_ */
