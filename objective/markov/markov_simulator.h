
#ifndef MARKOV_H_
#define MARKOV_H_

#include "alias/ransampl.h"
#include "stats/cdf.h"

#include <random>
#include <functional>

#include "markov_chain.h"


class MarkovSimulator
{
private:
	int nstates;
	ransampl_ws** comps;
	double *lambdas;

public:
	MarkovSimulator(const MarkovChain& args);
	~MarkovSimulator();

	MarkovSimulator& operator=(const MarkovChain& args);

	void sample(Cdf& cdf, int ntimes) { sample(cdf, 0, nstates-1, ntimes); }
	void sample(Cdf& cdf, int initialState, int hittingState, int ntimes);

	int get_n_states() { return nstates; }


	double simulate(
			Cdf& cdf,
			Cdf& tmp,
			double tol,
			std::function<double()> unif);

	bool communicative(const double minimum) const;
};

//double markov_compare_chain_to_dist(Markov& markov, Cdf& cdf, double tolerance);

#endif
