/*
 * local_search.h
 *
 *  Created on: Mar 29, 2016
 *      Author: default
 */

#ifndef LOCAL_LOCAL_SEARCH_H_
#define LOCAL_LOCAL_SEARCH_H_

#include "../markov/markov_simulator.h"
#include "local/local_search_params.h"



void local_search(MarkovSimulator& original, MarkovSimulator& result, LocalGeneticSearchParams& params);
void local_search_simple(Cdf& desired, MarkovChain& args, int maxiters, double tol);

void local_search_simple_expm(const SummedCdf& desired, MarkovChain& initialChain, int maxiters, double tol);
void local_search_simple_sim(Cdf& desired, MarkovChain& args, int maxiters, double tol);


#endif /* LOCAL_LOCAL_SEARCH_H_ */
