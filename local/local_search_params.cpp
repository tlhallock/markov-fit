/*
 * LocalGeneticSearchParams.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: default
 */

#include "local_search_params.h"

LocalGeneticSearchParams::LocalGeneticSearchParams(Cdf& cdf) :
	orig{orig},
	max_iters{1000},
	pop_size{20}
{

}

LocalGeneticSearchParams::~LocalGeneticSearchParams()
{
}

