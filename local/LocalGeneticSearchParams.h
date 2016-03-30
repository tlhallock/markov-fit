/*
 * LocalGeneticSearchParams.h
 *
 *  Created on: Mar 29, 2016
 *      Author: default
 */

#ifndef LOCAL_LOCALGENETICSEARCHPARAMS_H_
#define LOCAL_LOCALGENETICSEARCHPARAMS_H_

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

#endif /* LOCAL_LOCALGENETICSEARCHPARAMS_H_ */
