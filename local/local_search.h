/*
 * local_search.h
 *
 *  Created on: Mar 29, 2016
 *      Author: default
 */

#ifndef LOCAL_LOCAL_SEARCH_H_
#define LOCAL_LOCAL_SEARCH_H_

#include "local/local_search_params.h"
#include "markov.h"

void local_search(Markov& original, Markov& result, LocalGeneticSearchParams& params);



#endif /* LOCAL_LOCAL_SEARCH_H_ */
