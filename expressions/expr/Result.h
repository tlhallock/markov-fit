/*
 * Result.h
 *
 *  Created on: Apr 5, 2016
 *      Author: default
 */

#ifndef EXPR_RESULT_H_
#define EXPR_RESULT_H_

#include <iostream>

class Result
{
	int m;
	int n;

//	int maxM, maxN;

	double *vals;
public:
	Result(int m, int n);
	Result(const Result* o);
	virtual ~Result();

	Result& operator =(const Result& o);

	int rows() const { return m; }
	int cols() const { return n; }

	double value(int i, int j) const { return vals[i * n + j]; }
	void set(int i, int j, double val) { vals[i * n + j] = val; }

	bool is_scalar() const;

	void print(std::ostream& out) const;
};

#endif /* EXPR_RESULT_H_ */
