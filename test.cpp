

#include <iostream>
#include <random>
#include <cstdlib>      // std::rand, std::srand
#include <ctime>



#include "markov.h"
#include "local/local_search.h"


static void testDiff()
{
  //  Cdf cdf1(500, 0, 1);
  //  for (int i=0;i<100;i++)
  //    cdf1.sample(unif1(gen));


  //  Cdf cdf2(500, 0, 1);
  //  for (int i=0;i<1000;i++)
  //    cdf2.sample(unif2(gen));

  //  std::cout << "The difference is: " << cdf1.compare(&cdf2) << std::endl;
  
}


Cdf * createUnifCdf(int res, int numSamples)
{
	Cdf *cdf = new Cdf(res, 0, 3);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> unif(0, 1);
	for (int i=0;i<numSamples;i++)
	{
		double d = unif(gen);
		cdf->sample(d);
	}
	
	return cdf;
}

int main(int argc, char **argv)
{
	std::srand ( unsigned ( std::time(0) ) );
  
  
	Args args(3);
	args.randomize(5);
	args.write("output/markov.txt");
	
//	Args args("output/markov.txt");
	
	Cdf *unif = createUnifCdf(100, 10000);
	
	unif->print("output/unif_plot.m", "unif");
	
	
	Markov markov(args);
	double diff = compare_chain_to_dist(markov, *unif, 1e-2);
	
	Markov result{3};
	local_search(markov, result, -1);

	
	delete unif;
	
	return 0;
}
