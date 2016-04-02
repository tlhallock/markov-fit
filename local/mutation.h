/*
 * Mutation.h
 *
 *  Created on: Mar 29, 2016
 *      Author: default
 */

#ifndef LOCAL_MUTATION_H_
#define LOCAL_MUTATION_H_

#include <random>

#include "../markov/markov_simulator.h"

class Mutation
{
private:
	int n;
	double radius;
	double *mods;

	void normalize();
public:
	Mutation(int n);
	Mutation(Mutation& m);

	virtual ~Mutation();

	void set_radius(double r) { radius = r; }

	void randomize(std::mt19937& gen, std::uniform_real_distribution<>& unif);
	void mutate(double percent, std::mt19937& gen, std::uniform_real_distribution<>& unif);


	void cross(Mutation& m);
	void apply(const MarkovSimulator& original, MarkovSimulator& out) const;
};

#endif /* LOCAL_MUTATION_H_ */
