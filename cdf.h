

#ifndef CDF_H_
#define CDF_H_

#include <string>

class Cdf
{
private:
	int N;
	int count;
	double lower, upper;
	int *counts;
	double *F;

	bool summed;
public:
	Cdf(const int N, const double min, const double max);
	~Cdf();

	void reset();
	void merge(const Cdf& other);
	double compare(Cdf& other);

	void sample(const double value);

	void sum();
	
	int get_n() const { return N; }
	int get_lower() const { return lower; }
	int get_upper() const { return upper; }
	
	void print(const char *filename, const std::string& name);
	
	void debug();
};



#endif

