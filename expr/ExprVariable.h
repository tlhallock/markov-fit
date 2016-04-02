/*
 * ExprVariable.h
 *
 *  Created on: Apr 2, 2016
 *      Author: thallock
 */

#ifndef EXPR_EXPRVARIABLE_H_
#define EXPR_EXPRVARIABLE_H_

class ExprVariable {
	int index;
public:
	ExprVariable(int index) : index{index} {}
	virtual ~ExprVariable() {}


	virtual ExpressionRename* clone() { return new ExprVariable{index}; }
	virtual ExpressionRename* differentiate(const int variable)
	{
		if (index == variable) return new ExprOne{};
		return ExprZero{};
	}
	virtual expr_type get_type() { return EXPRESSION_TYPE_VARIABLE; }

	virtual ExpressionRename* simplify() { return this; };
	virtual ExpressionRename* evaluate(const Dictionary& dictionary)
	{
		if (dictionary.is_known(index))
		{
			return new ExprValue{dictionary.get(index)};
		}
		return clone();
	}
	virtual void print(std::ostream& out, int indentation)
	{
		for (int i=0;i<indentation;i++)
			out << '\t';
		out << "variable[" << index << "]\n";
	}
};

#endif /* EXPR_EXPRVARIABLE_H_ */
