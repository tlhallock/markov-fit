

#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>
#include <functional>


#include "local/local_search.h"
#include "markov/generator.h"
#include "markov/markov_simulator.h"

#include "test/test_distributions.h"
#include "global/random_search.h"



Cdf * testDiff()
{

  //  Cdf cdf1(500, 0, 1);
  //  for (int i=0;i<100;i++)
  //    cdf1.sample(unif1(gen));


  //  Cdf cdf2(500, 0, 1);
  //  for (int i=0;i<1000;i++)
  //    cdf2.sample(unif2(gen));

  //  std::cout << "The difference is: " << cdf1.compare(&cdf2) << std::endl;
	return nullptr;
}

Cdf *get_simulated_cdf(Generator *generator, Cdf *range)
{
	const double TOLERANCE = 1e-3;
	std::random_device rd;
	std::mt19937 gen{rd()};
	std::normal_distribution<> normal{0, 1};
	std::uniform_real_distribution<> unif{0, 1};

	Cdf *returnValue = new Cdf{range->getCdf().bounds()};
	Cdf tmp{range->getCdf().bounds()};

	MarkovChain chain {generator->get_size() };
	generator->assign(chain);

	MarkovSimulator simulator{chain};
	simulator.simulate(*returnValue, tmp, TOLERANCE, [&unif, &gen]() { return unif(gen); });

	return returnValue;
}


int main(int argc, char **argv)
{
	std::srand ( unsigned ( std::time(0) ) );

	int num_states = 3;


	Cdf *desired = create_cauchy_dist(100, 100000, 10, 3);
	desired->print("output/cauchy.m", "cauchy");

//	Generator *best = global_random_search(*desired, num_states);
	Generator *best = global_multistart_local_search(*desired, num_states);

	best->writeMatlab("output/generator.m");

	Cdf *found = get_simulated_cdf(best, desired);
	found->print("output/best_cdf.m", "gen_cdf");

	delete desired;
	delete best;

	return 0;
}
