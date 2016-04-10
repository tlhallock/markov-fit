/*
 * ExprBinary.h
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#ifndef EXPR_EXPRPARENT_H_
#define EXPR_EXPRPARENT_H_

#include "ExpressionRename.h"

#include <list>

class ExprParent : public ExpressionRename {
private:
	char type;
protected:
	std::list<ExpressionRename *> children;

	void collapse();
	virtual ExprParent *newOne() const = 0;
public:
	ExprParent(char c);
	virtual ~ExprParent();

	ExpressionRename *clone() const;

	virtual ExpressionRename* simplify(const SimplificationRules& rules);
	ExpressionRename* substitute(const Dictionary& dictionary) const;

	virtual void print(std::ostream& out, int indentation,
			const ExpressionOutputFlags& flags = ExpressionOutputFlags{}) const;

	bool contains_variable(int variable) const;

	std::list<ExpressionRename*>& get_children();
};

void print_list(const std::list<ExpressionRename *> list, char c, std::ostream& out, int indentation, const ExpressionOutputFlags& flags);


#endif /* EXPR_EXPRPARENT_H_ */
