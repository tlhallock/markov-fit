
#include "markov.h"

#include <random>
#include <tgmath.h>
#include <cstdlib>
#include <iostream>

Markov::Markov(const Args& args) :
  nstates{args.get_size()},
  comps{(ransampl_ws **) malloc (args.get_size() * sizeof (*comps))},
  lambdas(new double[args.get_size()])
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
double compare_chain_to_dist(Markov& markov, Cdf& orig, double tolerance)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> unif1(0, 1);
   
	double prev_diff = -1;
	double change	 = 1e300;
   
	Cdf comp(orig.get_n(), orig.get_lower(), orig.get_upper());
	
	const int initialState = 0;
	const int hittingState = markov.nstates-1;
	
	int tries = 0;
	do
	{
		for (int i=0;i<ITERATIONS;i++)
		{
			int state = initialState;

			double time = 0;
			while (state != hittingState)
			{
				time += -log(unif1(gen)) / markov.lambdas[state];
				state = ransampl_draw(markov.comps[state], unif1(gen), unif1(gen));
			}
			
			if (time < orig.get_upper())
				comp.sample(time);
		}
		
		double diff = comp.compare(orig);
		change = diff - prev_diff;
		if (change < 0) change = -change;
		prev_diff = diff;
	} while (change >= tolerance && tries++ < 10);
	
	comp.print("output/approximation.m", "markov");
     
     return prev_diff;
}