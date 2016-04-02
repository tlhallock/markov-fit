/*
 * Expression.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: default
 */

#include "Expression.h"

#include <stdlib.h>
#include <math.h>


expr *expr_und()
{
	expr *ret = (expr *) malloc (sizeof (*ret));
	ret->type = EXPRESSION_TYPE_ERROR;
	return ret;
}

expr *expr_multiply(expr *l, expr *r)
{
	expr *ret = (expr *) malloc (sizeof (*ret));
	ret->type = EXPRESSION_TYPE_MULTIPLICATION;
	ret->children.left = l;
	ret->children.right = r;
	return ret;
}
expr *expr_add(expr *l, expr *r)
{
	expr *ret = (expr *) malloc (sizeof (*ret));
	ret->type = EXPRESSION_TYPE_ADDITION;
	ret->children.left = l;
	ret->children.right = r;
	return ret;
}
expr *expr_divide(expr *l, expr *r)
{
	expr *ret = (expr *) malloc (sizeof (*ret));
	ret->type = EXPRESSION_TYPE_DIVISION;
	ret->children.left = l;
	ret->children.right = r;
	return ret;
}
expr *expr_subtract(expr *l, expr *r)
{
	expr *ret = (expr *) malloc (sizeof (*ret));
	ret->type = EXPRESSION_TYPE_SUBTRACTION;
	ret->children.left = l;
	ret->children.right = r;
	return ret;
}

expr *expr_value(double value)
{
	expr *ret = (expr *) malloc (sizeof (*ret));
	ret->type = EXPRESSION_TYPE_VALUE;
	ret->value = value;
	return ret;
}
expr *expr_variable(int index)
{
	expr *ret = (expr *) malloc (sizeof (*ret));
	ret->type = EXPRESSION_TYPE_VARIABLE;
	ret->index = index;
	return ret;
}

void  expr_free(expr *e)
{
	switch (e->type)
	{
	case EXPRESSION_TYPE_VALUE:
	case EXPRESSION_TYPE_VARIABLE:
	case EXPRESSION_TYPE_ERROR:
		break;
	case EXPRESSION_TYPE_ADDITION:
	case EXPRESSION_TYPE_SUBTRACTION:
	case EXPRESSION_TYPE_DIVISION:
	case EXPRESSION_TYPE_MULTIPLICATION:
		expr_free(e->children.left);
		expr_free(e->children.right);
		break;
	}
	free(e);
}

expr *expr_differentiate(expr *e)
{
	switch (e->type)
	{
	case EXPRESSION_TYPE_VALUE:
		return expr_value(e->value);
	case EXPRESSION_TYPE_VARIABLE:
		return expr_variable(e->index);
	case EXPRESSION_TYPE_ADDITION:
		return expr_add(expr_clone(e->children.left), expr_clone(e->children.right));
	case EXPRESSION_TYPE_SUBTRACTION:
		return expr_subtract(expr_clone(e->children.left), expr_clone(e->children.right));
	case EXPRESSION_TYPE_DIVISION:
		return expr_divide(expr_clone(e->children.left), expr_clone(e->children.right));
	case EXPRESSION_TYPE_MULTIPLICATION:
		return expr_multiply(expr_clone(e->children.left), expr_clone(e->children.right));
	case EXPRESSION_TYPE_ERROR:
		return expr_und();
	default:
		return (expr *) 0;
	}
}
expr *expr_simplify(expr *e)
{

}

expr *expr_clone(expr *e)
{
	switch (e->type)
	{
	case EXPRESSION_TYPE_VALUE:
		return expr_value(e->value);
	case EXPRESSION_TYPE_VARIABLE:
		return expr_variable(e->index);
	case EXPRESSION_TYPE_ADDITION:
		return expr_add(expr_clone(e->children.left), expr_clone(e->children.right));
	case EXPRESSION_TYPE_SUBTRACTION:
		return expr_subtract(expr_clone(e->children.left), expr_clone(e->children.right));
	case EXPRESSION_TYPE_DIVISION:
		return expr_divide(expr_clone(e->children.left), expr_clone(e->children.right));
	case EXPRESSION_TYPE_MULTIPLICATION:
		return expr_multiply(expr_clone(e->children.left), expr_clone(e->children.right));
	case EXPRESSION_TYPE_ERROR:
		return expr_und();
	default:
		return (expr *) 0;
	}
}
static void  expr_print_ind(expr *e, FILE *f, int indet)
{

}
void  expr_print(expr *e, FILE *f)
{
	char c = '?';

	switch (e->type)
	{
	case EXPRESSION_TYPE_ERROR:
		fprintf(f, "ERROR");
		return;
	case EXPRESSION_TYPE_VALUE:
		fprintf(f, "(%lf)", e->value);
		return;
	case EXPRESSION_TYPE_VARIABLE:
		fprintf(f, "(q[%d])", e->index);
		return;
	case EXPRESSION_TYPE_ADDITION:
		c = '+';
		break;
	case EXPRESSION_TYPE_SUBTRACTION:
		c = '-';
		break;
	case EXPRESSION_TYPE_DIVISION:
		c = '/';
		break;
	case EXPRESSION_TYPE_MULTIPLICATION:
		c = '*';
		break;
	}

	fputc('(', f);
	expr_print(e->children.left, f);
	fputc(')', f);
	fputc(c, f);
	fputc('(', f);
	expr_print(e->children.left, f);
	fputc(')', f);
}


double evaluate(expr *e, dictionary *d)
{
	switch (e->type)
	{
	case EXPRESSION_TYPE_VALUE:
		return e->value;
	case EXPRESSION_TYPE_VARIABLE:
		if (e->index < 0 || e->index >= d->max)
			printf("BAD STUFF!!!!");
		return d->vals[e->index];
	case EXPRESSION_TYPE_ADDITION:
		return evaluate(e->children.left, d) + evaluate(e->children.right, d);
	case EXPRESSION_TYPE_SUBTRACTION:
		return evaluate(e->children.left, d) - evaluate(e->children.right, d);
	case EXPRESSION_TYPE_DIVISION:
		return evaluate(e->children.left, d) / evaluate(e->children.right, d);
	case EXPRESSION_TYPE_MULTIPLICATION:
		return evaluate(e->children.left, d) * evaluate(e->children.right, d);
	case EXPRESSION_TYPE_MATRIX:
		throw 1;
	case EXPRESSION_TYPE_ERROR:
	default:
		return NAN;
	}
}









