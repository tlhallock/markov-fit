/*
 * ExprMatrix.h
 *
 *  Created on: Apr 2, 2016
 *      Author: default
 */

#ifndef EXPR_EXPRMATRIX_H_
#define EXPR_EXPRMATRIX_H_

#include "ExpressionRename.h"

#include <list>

class ExprMatrix : public ExpressionRename
{

private:
	int m, n;
	ExpressionRename **elems;


	friend ExprMatrix *expr_matrix_simplify_sum(const std::list<ExpressionRename *>& list);
public:
	ExprMatrix(int m, int n);
	virtual ~ExprMatrix();

	int get_m() const { return m; }
	int get_n() const { return n; }

	ExpressionRename* get(int i, int j);
	const ExpressionRename* get(int i, int j) const;
	void set(int i, int j, ExpressionRename *expr);

	ExpressionRename* multiply(const ExprMatrix* expr) const;

	ExpressionRename* clone() const;
	ExpressionRename* differentiate(const int variable) const;
	expr_type get_type() const;
	ExpressionRename* simplify(const SimplificationRules& rules);
	ExpressionRename* evaluate(const Dictionary& dictionary) const;
	void print(std::ostream& out, int indentation, const ExpressionOutputFlags& flags = ExpressionOutputFlags{}) const;
	bool contains_variable(int variable) const;

	ExpressionRename* to_expr() const;
};

/** This should return an expression! **/
ExprMatrix *expr_matrix_simplify_sum(const std::list<ExpressionRename *>& list);

#endif /* EXPR_EXPRMATRIX_H_ */
