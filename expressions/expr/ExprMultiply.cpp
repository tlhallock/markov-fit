/*
 * ExprMultiply.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#include "ExprMultiply.h"

#include "ExprZero.h"
#include "ExprAddition.h"
#include "ExprValue.h"
#include "ExprMatrix.h"
#include "ExprOne.h"

#include <algorithm>


ExprMultiply::ExprMultiply(ExpressionRename* l, ExpressionRename* r) :
		ExprParent { '*' }
{
	children.push_back(l);
	children.push_back(r);
}

ExprMultiply::ExprMultiply() :
	ExprParent{'*'}
{
}


ExprMultiply::~ExprMultiply() {}


ExprParent* ExprMultiply::newOne() const
{
	return new ExprMultiply{};
}

ExpressionRename* ExprMultiply::differentiate(const int variable) const
{
	ExprAddition *addition = new ExprAddition{};

	int index = 0;

	const auto e1 = children.end();
	for (auto i1 = children.begin(); i1 != e1; ++i1)
	{
		ExprMultiply * multiply = new ExprMultiply{};

		int count = 0;

		const auto e2 = children.end();
		for (auto i2 = children.begin(); i2 != e2; ++i2)
		{
			if (count++ == index)
				multiply->multiply((*i1)->differentiate(variable));
			else
				multiply->multiply((*i1)->clone());
		}

		addition->add(multiply);
		index++;
	}

	return addition;
}

expr_type ExprMultiply::get_type() const
{
	return EXPRESSION_TYPE_MULTIPLICATION;
}

namespace {
void multiply_matrices(std::list<ExpressionRename*>& mats)
{
	const auto end = mats.end();
	auto it = mats.begin();

	while (it != end)
	{
		auto next = std::next(it);
		if (next == end ||
			(*it  )->get_type() != EXPRESSION_TYPE_MATRIX ||
			(*next)->get_type() != EXPRESSION_TYPE_MATRIX)
		{
			it++;
			continue;
		}

		ExprMatrix *m1 = (ExprMatrix *)(*it);
		mats.erase(it++);
		ExprMatrix *m2 = (ExprMatrix *)(*it);
		mats.erase(it++);

		ExprMatrix *res = m1->multiply(m2);
		mats.insert(it, expr_simplify(res));

		delete m1;
		delete m2;
	}

	if (mats.size() == 0)
	{
		std::cout << "Problem here." << std::endl;
		throw 1;
	}
}
}

ExpressionRename* ExprMultiply::simplify(const SimplificationRules& rules)
{
	if (children.size() == 1)
		return children.front()->clone();

	//		if (children.size() == 0)
	//			return none();
	ExprParent::simplify(rules);
	ExprParent::collapse();

	// sort all the values/variables/zeros/ones to the front

	if (rules.simplify_matrix_multiplication && 1 <= std::count_if(children.begin(), children.end(), [](const ExpressionRename *r)
		{ return r->get_type() == EXPRESSION_TYPE_MATRIX; }))
	{
		// clean up all consecutive matrix multiplications...
		multiply_matrices(children);

//		const auto end = children.end();
//		auto it = children.begin();
//
//		while (it != end)
//		{
//			if ((*it)->get_type() != EXPRESSION_TYPE_MATRIX)
//			{
//				it++;
//				continue;
//			}
//			ExprMatrix *m1 = (*it);
//			if (++it != end && (*it)->get_type() != EXPRESSION_TYPE_MATRIX)
//			{
//
//			}
//
//			ExprMatrix *valexpr = (ExprMatrix *) (*it);
//			children.erase(it++);
//			matrices.push_back(valexpr);
//		}
//
//		// could do something smarter...
//		ExprMatrix *m = nullptr;
//		const auto e = matrices.end();
//		for (auto i = matrices.begin(); i != e; ++i)
//		{
//			if (m == nullptr)
//			{
//				m = *i;
//				continue;
//			}
//			// UGLY!!!!
//			ExprMatrix *n = m->multiply(*i);
//			delete m;
//			delete *i;
//			m = n;
//		}
//
//		children.push_back(expr_simplify(m));
	}

	// TODO: clean up all matrix-scalar multiplications...

	const auto end = children.end();
	auto it = children.begin();
	while (it != end)
	{
		ExpressionRename *child;
		switch ((*it)->get_type())
		{
		case EXPRESSION_TYPE_ZERO:
			return new ExprZero{};
		case EXPRESSION_TYPE_ONE:
			child = (*it);
			children.erase(it++);
			delete child;
			break;
		default:
			++it;
		}
	}

	if (children.size() == 0)
	{
		return new ExprOne{};
	}

	return this;
}

void ExprMultiply::multiply(ExpressionRename* factor)
{
	children.push_back(factor);
}

//
//ExpressionRename* ExprMultiply::substitute(
//		const Dictionary& dictionary) const
//{
//	ExprMultiply* multiplication = (ExprMultiply *) ExprParent::substitute(dictionary);
//
//	// I should break this up between a simplify/substitute/evaluate
//
//	const auto end = multiplication->children.end();
//
//
//
//
//	return multiplication;
//}

void multiply_it(double val, Result *other)
{
	int rows = other->rows();
	int cols = other->cols();
	for (int i=0;i<rows;i++)
	{
		for (int j=0;j<cols;j++)
		{
			other->set(i, j, other->value(i, j) * val);
		}
	}
}

/** Could evaluate WAY more multiplications than necessary... **/
Result* ExprMultiply::evaluate() const
{
	Result *previus = nullptr;
	int lastRows;

	const auto end = children.end();
	auto it = children.begin();

	Result *current = (*it)->evaluate();
	++it;
	while (it != end)
	{
		Result *next = (*it)->evaluate();
		if (next->rows() != current->cols())
		{
			if (current->is_scalar())
			{
				multiply_it(current->value(0, 0), next);
				delete current;
				current = next;
			}
			else if (next->is_scalar())
			{
				multiply_it(next->value(0, 0), current);
				delete next;
			}
			else
			{
				throw 1;
			}
		}
		else
		{
			int mk = next->rows();
			int nr = current->rows();
			int nc = next->cols();
			Result *building = new Result{nr, nc};
			for (int i=0;i<nr;i++)
			{
				for (int j=0;j<nc; j++)
				{
					double val = 0;

					for (int k=0;k<mk;k++)
						val += current->value(i, k) * next->value(k, j);

					building->set(i, j, val);
				}
			}

			delete current;
			delete next;
			current = building;
		}

		++it;
	}

	return current;
}

// FUTURE WORK: be WAY smarter
//
//bool evaluated = true;
//while (evaluated)
//{
//	// Simplify values...
//	{
//		int count = 0;
//		bool removed = false;
//		double value = 1.0;
//		const auto end = multiplication->children.end();
//		auto it = multiplication->children.begin();
//
//		while (it != end)
//		{
//			if ((*it)->get_type() != EXPRESSION_TYPE_VALUE)
//			{
//				it++;
//				continue;
//			}
//
//			ExprValue *valexpr = (ExprValue *) (*it);
//			removed = true;
//			multiplication->children.erase(it++);
//			value *= valexpr->get_value();
//			delete valexpr;
//			count++;
//		}
//
//		if (removed)
//		{
//			if (multiplication->children.empty())
//				return new ExprValue { value };
//
//			multiplication->children.push_front(
//					new ExprValue { value });
//
//			evaluated = count > 1;
//		}
//	}
//
//	// Simplify matrices
//	int count = std::count_if(multiplication->children.begin(), multiplication->children.end(), [](const ExpressionRename *r)
//	{
//		return r->get_type() == EXPRESSION_TYPE_MATRIX;
//	});
//	if (count > 1)
//	{
//		const auto end = multiplication->children.end();
//		auto it = multiplication->children.begin();
//
//		std::list<ExprMatrix *> matrices;
//
//		while (it != end)
//		{
//			if ((*it)->get_type() != EXPRESSION_TYPE_MATRIX)
//			{
//				it++;
//				continue;
//			}
//
//			ExprMatrix *valexpr = (ExprMatrix *) (*it);
//			multiplication->children.erase(it++);
//			matrices.push_back(valexpr);
//		}
//
//		// could do something smarter...
//
//		ExprMatrix *m = nullptr;
//		const auto e = matrices.end();
//		for (auto i=matrices.begin(); i!= e; ++i)
//		{
//			if (m == nullptr)
//			{
//				m = *i;
//				continue;
//			}
//			// UGLY!!!!
//			ExprMatrix *n = m->multiply(*i);
//			delete m;
//			delete *i;
//			m = n;
//		}
//
//		multiplication->children.push_back(m);
//	}
//}











