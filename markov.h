
#ifndef MARKOV_H_
#define MARKOV_H_

#include "alias/ransampl.h"
#include "args.h"
#include "cdf.h"


class Markov
{
	friend double compare_chain_to_dist(Markov& markov, Cdf& cdf, double tolerance);
private:
	int nstates;
	ransampl_ws** comps;
	double *lambdas;

public:
	Markov(const Args& args);
	~Markov();	

	void sample(Cdf& cdf, int ntimes) { sample(cdf, 0, nstates-1, ntimes); }
	void sample(Cdf& cdf, int initialState, int hittingState, int ntimes);

	int get_n_nstates() { return nstates; }
};

double compare_chain_to_dist(Markov& markov, Cdf& cdf, double tolerance);

#endif
