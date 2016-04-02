/*
 * ExprBinary.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#include "ExprParent.h"


ExpressionRename* ExprParent::simplify(const SimplificationRules& rules)
{
	if (children.size() == 1)
		return children.front()->clone();

	//		if (children.size() == 0)
	//			return none();
	auto end = children.end();
	for (auto it = children.begin(); it != end; ++it)
		children.insert(children.erase(it), expr_simplify(*it, rules));
	return this;
}

ExpressionRename* ExprParent::evaluate(
		const Dictionary& dictionary) const
{
	return clone();
}

void ExprParent::print(std::ostream& out, int indentation,
		const ExpressionOutputFlags& flags) const
{
	auto it = children.begin();
	auto end = children.end();

	if (flags.indent)
		for (int i = 0; i < indentation; i++)
			out << '\t';
	out << '(';

	if (flags.indent)
		out << '\n';

	(*it)->print(out, indentation + 1);
	++it;

	while (it != end)
	{
		if (flags.indent)
			for (int i = 0; i < indentation; i++)
				out << '\t';
		out << ')';

		if (flags.indent)
			out << '\n';
		out << type << '(';
		if (flags.indent)
			out << '\n';
		(*it)->print(out, indentation + 1);
		++it;
	}
	if (flags.indent)
		for (int i = 0; i < indentation; i++)
			out << '\t';
	out << ')';

	if (flags.indent)
		out << '\n';
}

std::list<ExpressionRename*>& ExprParent::get_children()
{
	return children;
}


ExprParent::ExprParent(char c) :
		type { c }
{
}

ExprParent::~ExprParent()
{
	auto it = children.begin();
	auto end = children.end();
	for (; it != end; ++it)
	{
		delete *it;
	}
}