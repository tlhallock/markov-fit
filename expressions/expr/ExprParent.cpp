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
//	if (children.size() == 0)
//	{
//		std::cout << "Empty multiplication..." << std::endl;
//	}

	std::list<ExpressionRename*> copy{children};
	children.clear();

//	{
//		std::cout << "About to simplify (" << copy.size() << ")" << std::endl;
//		auto end = copy.end();
//		for (auto it = copy.begin(); it != end; ++it)
//		{
//			(*it)->print(std::cout, 0);
//			std::cout << std::endl;
//		}
//	}

	auto end = copy.end();
	for (auto it = copy.begin(); it != end; ++it)
		children.push_back(expr_simplify(*it, rules));
	return this;
}

ExpressionRename* ExprParent::substitute(
		const Dictionary& dictionary) const
{
	// use <algorithm>

	ExprParent *returnValue = newOne();

	const auto end = children.end();
	for (auto it = children.begin(); it != end; ++it)
		returnValue->children.push_back((*it)->substitute(dictionary));

	return returnValue;
}

void ExprParent::print(std::ostream& out, int indentation,
		const ExpressionOutputFlags& flags) const
{
	print_list(children, type, out, indentation, flags);
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
	const auto end = children.end();
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



void print_list(const std::list<ExpressionRename *> list, char c, std::ostream& out, int indentation, const ExpressionOutputFlags& flags)
{
	if (list.size() == 0)
	{
		std::cout << "Nothing to print!!!!!!!!" << std::endl;
		throw 1;
	}
	auto it = list.begin();
	auto end = list.end();

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
		out << c << '(';
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
