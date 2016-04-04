/*
 * parser_utils.cpp
 *
 *  Created on: Apr 3, 2016
 *      Author: default
 */

#include "parser_utils.h"

ExpressionRename *createValue(double value)
{
	return new ExprValue {value};
}




