/*
 * Dictionary.h
 *
 *  Created on: Apr 1, 2016
 *      Author: thallock
 */

#ifndef EXPR_DICTIONARY_H_
#define EXPR_DICTIONARY_H_

class ExpressionRename;

class Dictionary {
	int n;
	ExpressionRename **values;

public:
	Dictionary(int n);
	virtual ~Dictionary();

	ExpressionRename *get(const int variable) const;
	void put(const int variable, const ExpressionRename& val);
	void put(const int variable, const ExpressionRename&& val);

	void clear();
};

#endif /* EXPR_DICTIONARY_H_ */
