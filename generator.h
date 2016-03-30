
#ifndef GENERATOR_H_
#define GENERATOR_H_

class Generator
{   
 private:
  int n;
  double *probs;
  
  
  void normalize();
  
 public:
	Generator(int n);
	Generator(const char *filename);
	~Generator();

	void randomize(double var);

	int get_size() const { return n; }
	double get_prob(int i, int j) const { return probs[n * i + j]; }
  
	void write(const char *filename);
	void writeMatlab(const char *filename);
};


#endif
