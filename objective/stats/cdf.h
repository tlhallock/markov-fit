

#ifndef CDF_H_
#define CDF_H_

#include <string>

// Should use inheritance...

class Stencil
{
public:
	int N;
	double lower, upper;

	Stencil(int N, double lower, double upper) :
		N{N},
		lower{lower},
		upper{upper} {}


	Stencil(const Stencil& s) : Stencil{s.N, s.lower, s.upper} {}

	bool operator==(const Stencil& other) const
	{
		return N == other.N && other.lower == other.lower && upper == other.upper;
	}

	int map(const double x) const
	{
		return (int) ((x - lower) / (upper - lower) * N);
	}

	double unmap(const int index) const
	{
		return lower + (upper - lower) * index / (double) N;
	}

};

class SummedCdf
{
private:
	Stencil stencil;
	double *F;

public:
	SummedCdf(const Stencil& stencil) :
		stencil{stencil},
		F{new double[stencil.N]} {}
	~SummedCdf() { delete[] F; }

	void set(double x, double s)
	{
		int index = stencil.map(x);
		if (index < 0 || index > stencil.N)
		{
			throw -1;
		}
		set(index, s);

	}
	void set(int i, double s)
	{
		F[i] = s;
	}
	double get(const int i) const { return F[i]; }

	double compare(const SummedCdf& other) const
	{
		if (!(stencil == other.stencil))
			throw -1;

		double max = 0;
		for (int i=0;i<stencil.N;i++)
		{
			double diff = F[i] - other.F[i];
			if (diff < 0)
				diff = -diff;
			if (max < diff)
				max = diff;
		}

		return max;
	}

	SummedCdf& operator=(const SummedCdf& other)
	{
		for (int i=0;i<stencil.N;i++)
			F[i] = other.F[i];
		return *this;
	}

	const Stencil& bounds() const { return stencil; }

	void print(const char *filename, const char *name) const;
};



class Cdf
{
private:
	SummedCdf cached;

	bool summed;
	int count;
	int *counts;
public:
	Cdf(const Stencil& s);
	~Cdf();

	Cdf& operator=(const Cdf& other);

	void reset();
	void merge(const Cdf& other);
	double compare(Cdf& other);

	void sample(const double value);

	
	void print(const char *filename, const std::string& name);
	
	void sum();
	double get_moment(int moment) const;

	const SummedCdf& getCdf();
};




#endif

