
#include "markov/markov.h"

#include "constants.h"

#include <random>
#include <tgmath.h>
#include <cstdlib>
#include <iostream>

Markov::Markov(const Args& args) :
  nstates{args.get_size()},
  comps{(ransampl_ws **) malloc (args.get_size() * sizeof (*comps))},
  lambdas{new double[args.get_size()]}
  {
    for (int i=0;i<nstates;i++)
      {
	comps[i] = ransampl_alloc(nstates);
	ransampl_set(comps[i], args.get_distro(i));
        lambdas[i] = args.get_lambda(i);
      }
  }


Markov::~Markov()
{
  for (int i=0;i<nstates;i++)
    {
      ransampl_free(comps[i]);
    }
  free(comps);
  delete[] lambdas;
}

 void Markov::sample(Cdf& cdf, int initialState, int hittingState, int ntimes)
 {
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> unif1(0, 1);
   
   for (int i=0;i<ntimes;i++)
     {
       int state = initialState;

       double time = 0;
       while (state != hittingState)
	 {
	   time += -log(unif1(gen)) / lambdas[state];
	   state = ransampl_draw(comps[state], unif1(gen), unif1(gen));
	 }

       cdf.sample(time);
     }
 }
 
#define ITERATIONS 1000
double Markov::simulate(
		Cdf& cdf,
		Cdf& tmp,
		double tol,
		std::mt19937& gen,
		std::uniform_real_distribution<>& unif)
{
	const int initialState = 0;
	const int hittingState = nstates-1;

	double diff = 0.0;
	int tries = 0;
	do
	{
		tmp = cdf;

		for (int i=0; i<ITERATIONS; i++)
		{
			int state = initialState;

			double time = 0;
			while (state != hittingState)
			{
				time += -log(unif(gen)) / lambdas[state];
				state = ransampl_draw(comps[state], unif(gen), unif(gen));
			}

			cdf.sample(time);
		}

		double diff = tmp.compare(cdf);
	} while (diff <= tol && tries++ < 100);

	return diff;
}

Markov& Markov::operator =(const Args& args)
{
	if (nstates != args.get_size())
		throw SIZE_MISMATCH_IN_MARKOV_ASSIGN;
	for (int i = 0; i < nstates; i++)
	{
		ransampl_set(comps[i], args.get_distro(i));
		lambdas[i] = args.get_lambda(i);
	}

	return *this;
}


//
//bool Markov::communicative(const double minimum) const
//{
//
//	bool reachable[] = new bool[nstates];
//	for (int i=0;i<nstates;i++)
//		for (int j=0;j<nstates;j++)
//			reachable[i][j] = false;
//
//
//	for (int i=0;i<nstates;i++)
//	{
//		if (!reachable[i])
//			continue;
//		for (int j=0;j<nstates;j++)
//			if (get_prob())
//	}
//
//
//	delete[] reachable;
//
//}











//
//double markov_compare_chain_to_dist(Markov& markov, Cdf& orig, double tolerance)
//{
//	std::random_device rd;
//	std::mt19937 gen(rd());
//	std::uniform_real_distribution<> unif1(0, 1);
//
//	double prev_diff = -1;
//	double change = 1e300;
//
//	Cdf comp(orig.get_n(), orig.get_lower(), orig.get_upper());
//
//	int tries = 0;
//	do
//	{
//		markov.simulate(comp, ITERATIONS, gen, unif1);
//
//		double diff = comp.compare(orig);
//		change = diff - prev_diff;
//		if (change < 0)
//			change = -change;
//		prev_diff = diff;
//	} while (change >= tolerance && tries++ < 10);
//
//	comp.print("output/approximation.m", "markov");
//
//	return prev_diff;
//}
