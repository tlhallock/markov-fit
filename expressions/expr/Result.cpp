/*
 * Result.cpp
 *
 *  Created on: Apr 5, 2016
 *      Author: default
 */

#include "Result.h"

Result::Result(const Result* o) :
		Result { o->rows(), o->cols() }
{
}

Result::Result(int m, int n) :
		m { m },
		n { n },
		vals { new double [ m * n ] }
{
}

Result::~Result()
{
	delete[] vals;
}

Result& Result::operator =(const Result& o)
{
	if (m != o.m || n != o.n)
		throw 1;

	for (int i = 0; i < m * n; i++)
		vals[i] = o.vals[i];
	return *this;
}

bool Result::is_scalar() const
{
	return m == 1 && n == 1;
}

void Result::print(std::ostream& out) const
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			out << value(i, j) << ' ';
		out << '\n';
	}
}
