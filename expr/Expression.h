/*
 * Expression.h
 *
 *  Created on: Mar 29, 2016
 *      Author: default
 */

#ifndef EXPR_EXPRESSION_H_
#define EXPR_EXPRESSION_H_

typedef enum
{
	EXPRESSION_TYPE_VALUE,
	EXPRESSION_TYPE_VARIABLE,

	EXPRESSION_TYPE_ADDITION,
	EXPRESSION_TYPE_SUBTRACTION,
	EXPRESSION_TYPE_MULTIPLICATION,
	EXPRESSION_TYPE_DIVISION,

	EXPRESSION_TYPE_MATRIX,

	EXPRESSION_TYPE_ERROR,
} expr_type;


typedef struct
{
	expr *left;
	expr *right;
} child;

typedef struct expr_struct
{
	expr_type type;
	union
	{
		child children;
		double value;
		int index;
	};
} expr;

typedef struct
{
	int max;
	double *vals;
} dictionary;

expr *expr_und();
expr *expr_multiply(expr *l, expr *r);
expr *expr_add(expr *l, expr *r);
expr *expr_divide(expr *l, expr *r);
expr *expr_subtract(expr *l, expr *r);
expr *expr_value(double value);
expr *expr_variable(int index);
void  expr_free(expr *e);


expr *expr_differentiate(expr *e);
expr *expr_simplify(expr *e, int variable);

expr *expr_clone(expr *e);
void  expr_print(expr *e, FILE *f);

double evaluate(expr *e, dictionary *d);


#endif /* EXPR_EXPRESSION_H_ */
