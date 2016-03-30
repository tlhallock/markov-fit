/*
 * local_search.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: default
 */


#include "local/local_search.h"


void local_search(Markov& original, Markov& result, LocalGeneticSearchParams& params)
{
	Markov ** chains = new Markov*[params.get_pop_size()];

	for (int i=0;i<params.get_pop_size(); i++)
	{
		chains[i] = new Markov{original};
	}



	delete[] chains;
}
