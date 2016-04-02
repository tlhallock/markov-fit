/*
 * ExprBinary.h
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#ifndef EXPR_EXPRPARENT_H_
#define EXPR_EXPRPARENT_H_

#include "ExpressionRename.h"

#include <vector>

class ExprParent : public ExpressionRename {
protected:
	std::vector<ExpressionRename *> children;
	char type;
public:
	ExprParent(char c) : type{c} {}

	virtual ~ExprParent()
	{
		auto it = children.begin();
		auto end = children.end();
		for (; it != end; ++it)
		{
			delete *it;
		}
	}


	virtual ExpressionRename* clone() = 0;
	virtual ExpressionRename* differentiate(const int variable) = 0;
	virtual expr_type get_type() = 0;

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

	virtual void print(std::ostream& out, int indentation)
	{
		auto it = children.begin();
		auto end = children.end();

		for (int i=0;i<indentation;i++)
			out << '\t';
		out << "(\n";
		it->print(out, indentation+1);

		while (it != end)
		{
			for (int i=0;i<indentation;i++)
				out << '\t';
			out << ")\n" << type << "(\n";

			it->print(out, indentation+1);

			++it;
		}

		for (int i=0;i<indentation;i++)
			out << '\t';
		out << ")\n";
	}
};

#endif /* EXPR_EXPRPARENT_H_ */
