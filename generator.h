
#ifndef GENERATOR_H_
#define GENERATOR_H_

#include "args.h"

class Generator
{   
 private:
  int n;
  double *probs;
  
  void normalize();
  
 public:
	Generator(int n);
	Generator(const char *filename);
	Generator(const Args& markov);

	~Generator();

	void randomize(double var = 1.0);

	int get_size() const { return n; }
	double get_prob(int i, int j) const { return probs[n * i + j]; }
	void set_prob(int i, int j, double val) const { probs[n * i + j] = val; }
  
	void write(const char *filename);
	void writeMatlab(const char *filename);

	void assign(Args& markov) const;



	double get_distance(const Generator& other) const;
	void set_radius_from(const Generator& other, double radius = 1.0);
};


#endif
