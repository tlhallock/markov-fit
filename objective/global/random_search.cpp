/*
 * random_search.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: default
 */

#include "global/random_search.h"
#include "local/local_search.h"
#include "markov/mexp.h"

#include <random>


#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>

#include <chrono>






Generator *global_random_search(Cdf& desired, int ndim)
{
	const double TOLERANCE = 1e-3;
	const double M = 50;

	// Create random devices...
	std::random_device rd;
	std::mt19937 gen{rd()};
	std::normal_distribution<> normal{0, 1};
	std::uniform_real_distribution<> unif{0, M};

	// Create generators...
	Generator gen_current{ndim};
	Generator *gen_optimal = new Generator{ndim};
	gen_optimal->randomize([&unif, &gen]() { return unif(gen); });


	SummedCdf cdf_optimal {desired.getCdf().bounds()};
	SummedCdf cdf_current {desired.getCdf().bounds()};

	GslContext context{gen_optimal->get_size()};

	set_cdf(*gen_optimal, cdf_optimal, context);

	double current_distance;

	int count = 0;
	while (count++ < 1000)
	{
		gen_optimal->randomize([&unif, &gen]() { return unif(gen); });
		set_cdf(gen_current, cdf_current, context);

		double diff = cdf_current.compare(desired.getCdf());
		if (diff >= current_distance)
		{
			continue;
		}

		current_distance = diff;
		(*gen_optimal) = gen_current;
	}

	return gen_optimal;
}



Generator *global_multistart_local_search(Cdf& desired, int ndim)
{
	const double TOLERANCE = 1e-3;
	const double M = 50;

	// Create random devices...
	std::random_device rd;
	std::mt19937 gen{rd()};
	std::normal_distribution<> normal{0, 1};
	std::uniform_real_distribution<> unif{0, M};

	// Create generators...
	Generator gen_current{ndim};
	Generator *gen_optimal = new Generator{ndim};
	gen_optimal->randomize([&unif, &gen]() { return unif(gen); });


	SummedCdf cdf_optimal {desired.getCdf().bounds()};
	SummedCdf cdf_current {desired.getCdf().bounds()};

	GslContext context{gen_optimal->get_size()};

	set_cdf(*gen_optimal, cdf_optimal, context);

	double current_distance;

	int count = 0;
	while (count++ < 10)
	{
		std::cout << "Search " << count << std::endl;
		gen_optimal->randomize([&unif, &gen]() { return unif(gen); });
		local_search_simple_expm(desired.getCdf(), *gen_optimal, 1000, 1e-2);
		set_cdf(gen_current, cdf_current, context);

		double diff = cdf_current.compare(desired.getCdf());
		if (diff >= current_distance)
		{
			continue;
		}

		current_distance = diff;
		(*gen_optimal) = gen_current;
	}

	return gen_optimal;
}


