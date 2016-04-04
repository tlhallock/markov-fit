/*
 * ExprBinary.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#include "ExprParent.h"


ExpressionRename* ExprParent::simplify(const SimplificationRules& rules)
{
	// use <algorithm>
	if (children.size() == 1)
		return children.front()->clone();

	std::list<ExpressionRename*> copy{children};
	children.clear();

	auto end = copy.end();
	for (auto it = copy.begin(); it != end; ++it)
		children.push_back(expr_simplify(*it, rules));
	return this;
}

ExpressionRename* ExprParent::evaluate(
		const Dictionary& dictionary) const
{
	// use <algorithm>

	ExprParent *returnValue = newOne();

	const auto end = children.end();
	for (auto it = children.begin(); it != end; ++it)
		returnValue->children.push_back((*it)->evaluate(dictionary));

	return returnValue;
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

void ExprParent::collapse()
{
	expr_type ttype = get_type();
	const auto end = children.end();
	auto it = children.begin();
	while (it != end)
	{
		expr_type otype = (*it)->get_type();
		if (otype != ttype)
		{
			++it;
			continue;
		}

		ExprParent* child = (ExprParent*) ((*it));

		children.splice(it, child->get_children());
		children.erase(it++);
		delete child;
	}
}

ExpressionRename* ExprParent::clone() const
{
	ExprParent *c = newOne();


	// should be std::transform...

	const auto end = children.end();
	for (auto it = children.begin(); it != end; ++it)
	{
		c->children.push_back((*it)->clone());
	}

	return c;
}

bool ExprParent::contains_variable(int variable) const
{
	const auto end = children.end();
	for (auto it = children.begin(); it != end; ++it)
	{
		if ((*it)->contains_variable(variable))
			return true;
	}
	return false;
}
