/*
 * test_distributions.cpp
 *
 *  Created on: Apr 9, 2016
 *      Author: default
 */

#include "test/test_distributions.h"

#include <random>

Cdf * create_unif_dist(int res, int numSamples, double max)
{
	Cdf *cdf = new Cdf(Stencil { res, 0, max });

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> unif(0, 1);
	for (int i = 0; i < numSamples; i++)
	{
		double d = unif(gen);
		cdf->sample(d);
	}

	return cdf;
}

Cdf * create_chi_square(int res, int numSamples, double max, int numModes)
{
	std::default_random_engine generator;

	Cdf *cdf = new Cdf(Stencil { res, 0, max });

	const int NUM = 3;
	numModes = NUM;
	double modes[] = { 1.0, 5.0, 10.0 };
	for (int i = 0; i < numModes; i++)
	{
		std::chi_squared_distribution<double> distribution(modes[i]);
		for (int j=0;j<numSamples / numModes; j++)
		{
			cdf->sample(distribution(generator));
		}
	}

	return cdf;
}

#include <iostream>
Cdf *create_cauchy_dist(int res, int numSamples, double max, int numModes)
{
	std::default_random_engine generator;

	Cdf *cdf = new Cdf(Stencil { res, 0, max });

	const int NUM = 2;
	numModes = NUM;
	double x0[] = { 1.0, 4.0, 10.0 };
	double gamma[] = { 0.5, 1.0, 10.0 };
	for (int i = 0; i < numModes; i++)
	{
		std::cout << "Creating with a=" << x0[i] << " and b=" << gamma[i] << std::endl;
		std::cauchy_distribution<double> distribution(x0[i], gamma[i]);
		for (int j=0;j<numSamples / numModes; j++)
		{
			double number = distribution(generator);
			if (number < 0)
				number = -number;
			cdf->sample(number);
		}
	}

	return cdf;

}
