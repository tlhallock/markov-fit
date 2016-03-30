/*
 * Mutation.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: default
 */

#include "Mutation.h"



	double radius;
	double *mods;




void Mutation::normalize()
{
}

Mutation::Mutation(int n) :
	n{n},
	radius{1},
	mods{new double[n * (n+1)]}
{
}

Mutation::Mutation(Mutation& mutation) :
	n{mutation.n},
	radius{mutation.n},
	mods{new double[n * (n+1)]}
{
	for (int i=0;i<n*(n+1); i++)
		mods[i] = mutation.mods[i];
}


Mutation::~Mutation()
{
	delete[] mods;
}

void Mutation::randomize(std::mt19937& gen, std::uniform_real_distribution<>& unif)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> d(0, 1);
	for (int i=0;i<n*(n+1);i++)
		mods[i] = d(gen);

	normalize();
}

void Mutation::mutate(double percent, std::mt19937& gen, std::uniform_real_distribution<>& unif)
{
}

void Mutation::cross(Mutation& m)
{
}

void Mutation::apply(const Markov& original, Markov& out) const
{
}
