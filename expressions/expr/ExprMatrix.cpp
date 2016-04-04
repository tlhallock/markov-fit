/*
 * ExprMatrix.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: default
 */

#include "ExprMatrix.h"

#include "ExprZero.h"
#include "ExprAddition.h"
#include "ExprMultiply.h"

ExprMatrix::ExprMatrix(int m, int n) :
	m{m},
	n{n},
	elems{new ExpressionRename*[m * n]}
{
	for (int i=0;i<m*n;i++)
		elems[i] = nullptr;
}

ExprMatrix::~ExprMatrix()
{
	for (int i=0;i<m*n;i++)
		delete elems[i];
	delete[] elems;
}

ExpressionRename* ExprMatrix::get(int i, int j)
{
	return elems[i * n + j];
}
const ExpressionRename* ExprMatrix::get(int i, int j) const
{
	return elems[i * n + j];
}

void ExprMatrix::set(int i, int j, ExpressionRename* expr)
{
	elems[i * n + j] = expr;
}

ExpressionRename* ExprMatrix::multiply(const ExprMatrix* expr) const
{
	if (n != expr->m)
		throw 2;

	ExprMatrix * returnValue = new ExprMatrix{m, expr->n};

	for (int i=0;i<m;i++)
	{
		for (int j=0;j<expr->n;j++)
		{
			ExpressionRename *e = new ExprZero{};
			for (int k=0;k<n;k++)
			{
				ExpressionRename *e1 = get(i, k)->clone();
				ExpressionRename *e2 = get(k, j)->clone();
				ExpressionRename *m  = new ExprMultiply{e1, e2};
				e = new ExprAddition{e, m};
			}
			returnValue->set(i, j, e);
		}
	}

	for (int i=0;i<m*n;i++)
		returnValue->elems[i] = elems[i]->clone();

	return returnValue;
}

ExpressionRename* ExprMatrix::clone() const
{
	ExprMatrix * returnValue = new ExprMatrix{m, n};

	for (int i=0;i<m*n;i++)
		returnValue->elems[i] = elems[i]->clone();

	return returnValue;
}

ExpressionRename* ExprMatrix::differentiate(const int variable) const
{
	ExprMatrix * returnValue = new ExprMatrix{m, n};

	for (int i=0;i<m*n;i++)
		returnValue->elems[i] = elems[i]->differentiate(variable);

	return returnValue;
}

expr_type ExprMatrix::get_type() const
{
	return EXPRESSION_TYPE_MATRIX;
}

ExpressionRename* ExprMatrix::simplify(const SimplificationRules& rules)
{
	for (int i=0;i<m*n;i++)
		elems[i] = expr_simplify(elems[i], rules);
	return this;
}

ExpressionRename* ExprMatrix::evaluate(const Dictionary& dictionary) const
{
	ExprMatrix * returnValue = new ExprMatrix{m, n};

	for (int i=0;i<m*n;i++)
		returnValue->elems[i] = elems[i]->evaluate(dictionary);

	return returnValue;
}

void ExprMatrix::print(std::ostream& out, int indentation,
		const ExpressionOutputFlags& flags) const
{
	out << "[";

	for (int i=0;i<m;i++)
	{
		for (int j=0;j<n;j++)
		{
			get(i, j)->print(out, indentation, flags);
			out << ", ";
		}
		out << ";";
	}


	out << "]";
}

ExprMatrix *expr_matrix_simplify_sum(const std::list<ExpressionRename *>& list)
{
	bool is_matrix = list.front()->get_type() == EXPRESSION_TYPE_MATRIX;
	if (!is_matrix)
	{
		throw 3;
	}

	int m = ((ExprMatrix *) list.front())->get_m();
	int n = ((ExprMatrix *) list.front())->get_n();

	ExprMatrix *matrix = new ExprMatrix { m, n };
	for (int i = 0; i < m * n; i++)
		matrix->elems[i] = new ExprAddition { };

	const auto end = list.end();
	for (auto it = list.begin(); it != end; ++it)
	{
		if ((*it)->get_type() != EXPRESSION_TYPE_MATRIX)
			throw 1;

		ExprMatrix *mat = (ExprMatrix *) (*it);
		if (mat->get_m() != m || mat->get_n() != n)
			throw 2;

		for (int i = 0; i < m * n; i++)
			((ExprAddition *) matrix->elems[i])->add(mat->elems[i]->clone());
	}
	if (m != 1 || n != 1)
		return (ExprMatrix *) expr_simplify(matrix);
	return matrix;
}

bool ExprMatrix::contains_variable(int variable) const
{
	for (int i=0;i<m*n;i++)
		if (elems[i]->contains_variable(variable))
			return true;
	return false;
}

ExpressionRename* ExprMatrix::to_expr() const
{
	if (m != 1 || n != 1)
		throw -1;

	return elems[0]->clone();
}
