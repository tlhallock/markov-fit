

#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>



#include "markov.h"
#include "local/local_search.h"
#include "generator.h"


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
	Cdf *cdf = new Cdf(Stencil{res, 0, 3});

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

	Cdf *unif = createUnifCdf(100, 10000);
	unif->print("output/unif_plot.m", "unif");


	Args args{3};
	args.randomize(2);

	SummedCdf cdf{unif->getCdf().bounds()};

	local_search_simple_expm(unif->getCdf(), args, 100, 1e-3);
	
	delete unif;
	
	return 0;
}
