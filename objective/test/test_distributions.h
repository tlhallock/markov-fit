/*
 * test_distributions.h
 *
 *  Created on: Apr 9, 2016
 *      Author: default
 */

#ifndef TEST_TEST_DISTRIBUTIONS_H_
#define TEST_TEST_DISTRIBUTIONS_H_

#include "stats/cdf.h"

Cdf * create_unif_dist(int res, int numSamples, double max);
Cdf * create_chi_square(int res, int numSamples, double max, int numModes);
Cdf * create_cauchy_dist(int res, int numSamples, double max, int numModes);

#endif /* TEST_TEST_DISTRIBUTIONS_H_ */
