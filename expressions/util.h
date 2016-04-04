/*
 * util.h
 *
 *  Created on: Apr 3, 2016
 *      Author: default
 */

#ifndef UTIL_H_
#define UTIL_H_



template<typename T, typename Out, typename Operation>
void move_if(T& list, Out result, Operation op)
{
	const auto end = list.end();
	auto it = list.begin();


	while (it != end)
	{
		if (!op(*it))
		{
			++it;
			continue;
		}

		*result++ = *it;
		list.erase(it++);
	}
}



#endif /* UTIL_H_ */
