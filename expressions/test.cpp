/*
 * test.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#include <iostream>
#include <list>
#include "expressions.h"

int main(int argc, char **argv)
{
	ExpressionRename *three = new ExprValue{3};
	ExpressionRename *var = new ExprVariable{0};
	ExpressionRename *two = new ExprValue{2};

	ExpressionRename *mult = new ExprMultiply{three, var};
	ExpressionRename *expr = new ExprMultiply{mult, two};

	expr->print(std::cout, 0);

	expr = expr_simplify(expr);

	std::cout << std::endl;


	delete expr;



	return 0;
}

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
