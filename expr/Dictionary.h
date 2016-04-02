/*
 * Dictionary.h
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#ifndef EXPR_DICTIONARY_H_
#define EXPR_DICTIONARY_H_

class Dictionary {
	int n;
	bool *known;
	double *values;

public:
	Dictionary(int n) : n{n}, known{new bool[n]}, values{new double[n]} { clear(); }
	virtual ~Dictionary() { delete[] values; delete[] known; }

	bool is_known(const int variable) const
	{
		return variable < n && known[variable];
	}

	double get(const int variable) const
	{
		return values[variable];
	}

	void put(const int variable, const double value)
	{
		if (variable >= n) return;
		known[variable] = true;
		values[variable] = value;
	}

	void clear()
	{
		for (int i=0;i<n;i++)
			known[i] = false;
	}
};

#endif /* EXPR_DICTIONARY_H_ */
