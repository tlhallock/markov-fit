/*
 * local_search.h
 *
 *  Created on: Mar 29, 2016
 *      Author: default
 */

#ifndef LOCAL_LOCAL_SEARCH_H_
#define LOCAL_LOCAL_SEARCH_H_

#include "local/local_search_params.h"
#include "markov/markov.h"



void local_search(Markov& original, Markov& result, LocalGeneticSearchParams& params);
void local_search_simple(Cdf& desired, Args& args, int maxiters, double tol);

void local_search_simple_expm(const SummedCdf& desired, Args& initialChain, int maxiters, double tol);
void local_search_simple_sim(Cdf& desired, Args& args, int maxiters, double tol);


#endif /* LOCAL_LOCAL_SEARCH_H_ */
