/*
 * ExpressionOutputFlags.h
 *
 *  Created on: Apr 2, 2016
 *      Author: default
 */

#ifndef EXPR_EXPRESSIONOUTPUTFLAGS_H_
#define EXPR_EXPRESSIONOUTPUTFLAGS_H_

class ExpressionOutputFlags
{
public:
	bool indent;

	ExpressionOutputFlags() : indent{false} {}
	virtual ~ExpressionOutputFlags() {}
};

#endif /* EXPR_EXPRESSIONOUTPUTFLAGS_H_ */
