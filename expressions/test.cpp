/*
 * test.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

#include "expressions.h"
#include "parsers/parser.h"
#include "create_matrix_exp.h"


bool pred(int i)
{
	return i >= 3;
}
void pri(int i)
{
	std::cout << i << " ";
}

int main(int argc, char **argv)
{
	const int highest_order = 2;
	Dictionary dictionary {4};
	dictionary.put(0, ExprValue{1.0});
	dictionary.put(1, ExprValue{2.0});
	dictionary.put(2, ExprValue{3.0});
	dictionary.put(3, ExprValue{5.0});

//	for (int i=1;i<highest_order;i++)
//	{
		ExpressionRename *exp = create_matrix_exponential(2, 2);
		std::cout << "matrix exp: " << std::endl;
		exp->print(std::cout, 0);
		std::cout << std::endl;

		std::cout << "simplified: " << std::endl;
		exp = expr_simplify(exp);
		exp->print(std::cout, 0);
		std::cout << std::endl;

		std::cout << "simplified: " << std::endl;
		exp = expr_simplify(exp, SimplificationRules{true, true});
		exp->print(std::cout, 0);
		std::cout << std::endl;
//
//		std::cout << "substituted: " << std::endl;
//		ExpressionRename *value = exp->substitute(dictionary);
//		value->print(std::cout, 0);
//		std::cout << std::endl;
//
//		std::cout << "simplified: " << std::endl;
//		value = expr_simplify(value);
//		value->print(std::cout, 0);
//		std::cout << std::endl;
//
//		std::cout << "result: " << std::endl;
//		Result *res = value->evaluate();
//		res->print(std::cout);
//		std::cout << std::endl;

		delete exp;
//		delete value;
//		delete res;
//	}





//	ExprMatrix *mat1 = create_identity(3);
//	mat1->set(0, 3, new ExprValue{-5});
//	ExprMatrix *vector = new ExprMatrix{3, 1};
//	vector->set(0, 0, new ExprVariable{0});
//	vector->set(1, 0, new ExprVariable{1});
//	vector->set(2, 0, new ExprVariable{0});
//
//	ExpressionRename *mult = new ExprMultiply{mat1, vector};
//
//	mult->print(std::cout, 0);
//	std::cout << std::endl;
//
//	SimplificationRules rules;
//	rules.simplify_matrix_multiplication = true;
//	mult = (ExprMatrix *) expr_simplify(mult, rules);
//
//	mult->print(std::cout, 0);
//	std::cout << std::endl;
//
//
//	Dictionary d{2};
//	d.put(0, ExprValue{3});
//	d.put(1, ExprValue{6});
//
//	ExpressionRename *subs = mult->substitute(d);
//
//	subs->print(std::cout, 0);
//	std::cout << std::endl;
//
//
//
//	Result *res = subs->evaluate();
//	res->print(std::cout);
//	std::cout << std::endl;
//
//
//	delete res;
//	delete mult;
//	delete subs;







//	delete mat1;
//	delete mat2;






//	ExpressionRename *expr = parse("test.txt");
//	if (expr == nullptr)
//	{
//		std::cout << "No expression found." << std::endl;
//		return 0;
//	}
//
//	expr->print(std::cout, 0);
//	std::cout << std::endl;
//
//	delete expr;
}


//
//ExpressionRename *three = new ExprValue{3};
//ExpressionRename *var = new ExprVariable{0};
//ExpressionRename *two = new ExprValue{2};
//ExpressionRename *one = new ExprOne{};
//
//ExpressionRename *mult1 = new ExprMultiply{three, one};
//ExpressionRename *mult2 = new ExprMultiply{mult1, var};
//ExpressionRename *expr = new ExprMultiply{mult2, two};
//
//
//
//expr->print(std::cout, 0);
//std::cout << std::endl;
//
//expr = expr_simplify(expr);
//
//expr->print(std::cout, 0);
//std::cout << std::endl;
//
//
//delete expr;
//
//
//
//return 0;










//	std::list<int> l1;
//	l1.push_back(1);
//	l1.push_back(2);
//	l1.push_back(3);
//	l1.push_back(4);
//	l1.push_back(5);
//	l1.push_back(6);
//
//	std::list<int> l2;
//
////	std::remove_copy_if(l1.begin(), l1.end(), std::inserter{l2, std::next{l2.begin()}}, pred);
//	move_if(l1, std::back_insert_iterator<std::list<int> >{l2}, pred);
//
//	std::for_each(l1.begin(), l1.end(), pri);
//	std::cout << std::endl;
//	std::for_each(l2.begin(), l2.end(), pri);
//	std::cout << std::endl;
//
//	if (1) return 0;
//
//
//



//
//
//class ExprOne : public ExpressionRename
//{
//
//};
//
//class ExprZero : public ExpressionRename
//{
//
//};
//
//class ExprValue : public ExpressionRename
//{
//
//};
//
//class ExprVariable : public ExpressionRename
//{
//
//};
//
//class ExprParent : public ExpressionRename
//{
//	std::vector<ExpressionRename *> children;
//
//
//};
//





//
//std::list<int> l;
//
//l.push_back(1);
//l.push_back(2);
//l.push_back(3);
//l.push_back(4);
//l.push_back(5);
//l.push_back(6);
//
//std::list<int> l2;
//l2.push_back(20);
//l2.push_back(21);
//l2.push_back(22);
//
//int count = 0;
//for (auto it = l.begin(); it!= l.end(); ++it)
//{
//	if (++count == 2)
//	{
//		l.insert(l.erase(it), 10);
//	}
//}
//
//auto o = l.begin();
//std::advance(o, 3);
//l.splice(o, l2);
//std::cout << *o << std::endl << std::endl;
//l.erase(o);
//
//
//for (auto it = l.begin(); it!= l.end(); ++it)
//{
//	std::cout << *it << std::endl;
//}
//
//std::cout << std::endl;
//
//for (auto it = l2.begin(); it!= l2.end(); ++it)
//	std::cout << *it << std::endl;
//

//
//
//
