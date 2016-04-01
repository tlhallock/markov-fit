/*
 * local_search.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: default
 */


#include "local/local_search.h"


void local_search(Markov& original, Markov& result, LocalGeneticSearchParams& params)
{
	Args ** chains = new Args*[params.get_pop_size()];
	for (int i=0;i<params.get_pop_size(); i++)
	{
		chains[i] = new Args{original.get_n_states()};
		chains[i]->randomize(1.0);
	}


//
//	Generator gen2{args.get_size()};
//	gen2.randomize();
//
//	gen2.set_radius_from(generator, 1.0);






	for (int i=0;i<params.get_pop_size(); i++)
	{
		delete chains[i];
	}
	delete[] chains;
}
