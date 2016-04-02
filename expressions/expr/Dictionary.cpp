/*
 * Dictionary.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#include "Dictionary.h"
#include "ExpressionRename.h"

	ExpressionRename **values;

Dictionary::Dictionary(int n) :
	n{n},
	values{new ExpressionRename*[n]}
{
	for (int i=0;i<n;i++)
		values[i] = nullptr;
}

Dictionary::~Dictionary()
{
	for (int i=0;i<n;i++)
		delete values[i];
	delete[] values;
}

ExpressionRename *Dictionary::get(const int variable) const
{
	if (variable >= n)
		throw -1;
	if (values[variable] == nullptr)
		return nullptr;
	return values[variable]->clone();
}

void Dictionary::put(const int variable, const ExpressionRename& val)
{
	if (variable >= n)
		return;

	values[variable] = val.clone();
}
void Dictionary::put(const int variable, const ExpressionRename&& val)
{
	if (variable >= n)
		return;

	values[variable] = val.clone();
}

void Dictionary::clear()
{
	for (int i = 0; i < n; i++)
	{
		delete values[i];
		values[i] = nullptr;
	}
}
