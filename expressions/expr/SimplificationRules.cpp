/*
 * SimplificationRules.cpp
 *
 *  Created on: Apr 2, 2016
 *      Author: default
 */

#include "SimplificationRules.h"

SimplificationRules::SimplificationRules() :
	simplify_matrix_multiplication{false},
	simplify_exponentian{false} {}

SimplificationRules::~SimplificationRules()
{
}

SimplificationRules::SimplificationRules(bool m, bool e) :
		simplify_matrix_multiplication{m},
		simplify_exponentian{e}
{
}
