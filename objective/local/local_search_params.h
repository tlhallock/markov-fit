/*
 * LocalGeneticSearchParams.h
 *
 *  Created on: Mar 29, 2016
 *      Author: default
 */

#ifndef LOCAL_LOCAL_SEARCH_PARAMS_H_
#define LOCAL_LOCAL_SEARCH_PARAMS_H_

#include "stats/cdf.h"

class LocalGeneticSearchParams
{
private:
	Cdf& orig;

	int max_iters;
	int pop_size;
public:
	LocalGeneticSearchParams(Cdf& orig);
	virtual ~LocalGeneticSearchParams();


	int get_pop_size() { return pop_size; }
};

#endif /* LOCAL_LOCAL_SEARCH_PARAMS_H_ */
