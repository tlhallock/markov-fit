/*
 * random_search.h
 *
 *  Created on: Apr 9, 2016
 *      Author: default
 */

#ifndef GLOBAL_RANDOM_SEARCH_H_
#define GLOBAL_RANDOM_SEARCH_H_

#include "markov/generator.h"
#include "stats/cdf.h"



Generator *global_random_search(Cdf& desired, int ndim);
Generator *global_multistart_local_search(Cdf& desired, int ndim);




#endif /* GLOBAL_RANDOM_SEARCH_H_ */
