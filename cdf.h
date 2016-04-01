

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
	// Does not initialize with the others data!!!!!!!!!
	Cdf(const Cdf& dimensions) : Cdf{dimensions.get_n(), dimensions.get_lower(), dimensions.get_upper()} {}
	~Cdf();

	Cdf& operator=(const Cdf& other);
	Cdf& operator=(Cdf& other);

	void reset();
	void merge(const Cdf& other);
	double compare(Cdf& other);

	void sample(const double value);

	
	int get_n() const { return N; }
	double get_lower() const { return lower; }
	double get_upper() const { return upper; }
	
	void print(const char *filename, const std::string& name);
	
	void debug();

	void sum();
	double get_moment(int moment) const;
};



#endif

