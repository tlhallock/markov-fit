
#ifndef MATIRX_EXP_H_
#define MATRIX_EXP_H_

#include "../generator.h"


// Maybe we should add a lock here?
class Matlab
{
private:
	void *engine;
public:
	Matlab();
	~Matlab();
	
	double get_hitting_time(Generator& generator);
};



void quit();

#endif