/*
 * mexp.h
 *
 *  Created on: Apr 1, 2016
 *      Author: default
 */

#ifndef EXPM_MEXP_H_
#define EXPM_MEXP_H_

#include "markov/generator.h"
#include "stats/cdf.h"

class GslContext
{
private:
	int n;
	void *m1, *m2;

public:
	GslContext(int n);
	~GslContext();

	int get_size() { return n; }
	void *get_input() { return m1; }
	void *get_output() { return m2; }
};




void set_cdf(const Generator& gen, SummedCdf& cdf, GslContext& context);

#endif /* EXPM_MEXP_H_ */
