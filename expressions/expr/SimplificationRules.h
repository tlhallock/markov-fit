/*
 * SimplificationRules.h
 *
 *  Created on: Apr 2, 2016
 *      Author: default
 */

#ifndef EXPR_SIMPLIFICATIONRULES_H_
#define EXPR_SIMPLIFICATIONRULES_H_

class SimplificationRules
{
public:
	bool simplify_matrix_multiplication;
	bool simplify_exponentian;

	SimplificationRules();
	SimplificationRules(bool m, bool e);
	virtual ~SimplificationRules();
};

#endif /* EXPR_SIMPLIFICATIONRULES_H_ */
