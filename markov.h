
#ifndef MARKOV_H_
#define MARKOV_H_

#include "alias/ransampl.h"
#include "args.h"
#include "cdf.h"

#include <random>


class Markov
{
private:
	int nstates;
	ransampl_ws** comps;
	double *lambdas;

public:
	Markov(const Args& args);
	~Markov();

	Markov& operator=(const Args& args);

	void sample(Cdf& cdf, int ntimes) { sample(cdf, 0, nstates-1, ntimes); }
	void sample(Cdf& cdf, int initialState, int hittingState, int ntimes);

	int get_n_states() { return nstates; }


	double simulate(
			Cdf& cdf,
			Cdf& tmp,
			double tol,
			std::mt19937& gen,
			std::uniform_real_distribution<>& unif);

	bool communicative(const double minimum) const;
};

//double markov_compare_chain_to_dist(Markov& markov, Cdf& cdf, double tolerance);

#endif
