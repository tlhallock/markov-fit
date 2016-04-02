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

public:
	ExprParent(char c);
	virtual ~ExprParent();


	virtual ExpressionRename* simplify(const SimplificationRules& rules);

	virtual ExpressionRename* evaluate(const Dictionary& dictionary) const;

	virtual void print(std::ostream& out, int indentation,
			const ExpressionOutputFlags& flags) const;

	std::list<ExpressionRename*>& get_children();
};

#endif /* EXPR_EXPRPARENT_H_ */
