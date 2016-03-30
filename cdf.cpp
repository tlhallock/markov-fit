
#include "cdf.h"
#include "constants.h"

#include <iomanip>
#include <fstream>
#include <limits>
//#include <random>

Cdf::Cdf(int N, double min, double max) :
	N{N},
	count{0},
	lower{min},
	upper{max},
	counts{new int[N+1]},
	F{new double[N+1]},
	summed{false}
{
	reset();
}


Cdf::~Cdf()
{
	delete[] counts;
	delete[] F;
}

void Cdf::reset()
{
  for (int i=0;i<N;i++)
    counts[i] = 0;
  count = 0;
  summed = false;
}

void Cdf::merge(const Cdf& other)
{
	if (N != other.N || lower != other.lower || upper != other.upper)
		throw BAD_CDF_MERGE_EXCEPTION;
	
	for (int i=0;i<N;i++)
		counts[i] += other.counts[i];

	count += other.count;
}

double Cdf::compare(Cdf& other)
{
	if (N != other.N || lower != other.lower || upper != other.upper)
		throw BAD_CDF_COMPARE_EXCEPTION;
	
	sum(); other.sum();

	double max = 0;
	for (int i=0;i<N;i++)
	{
		double diff = F[i] - other.F[i];
		if (diff < 0)
			diff = -diff;
		if (max < diff)
			max = diff;
//		sum += diff * diff;
	}

	return max;
}

#include <iostream>

void Cdf::sample(const double value)
{
	summed = false;
	if (value < lower || value > upper)
	  {
	    //std::cout << "Ignoring value not in range." << std::endl;
	    		throw BAD_CDF_ARGUMENT_OUT_OF_RANGE;
	    return;
	  }
	  
	  
	int index = (int) ((value - lower) * N / (upper - lower));
	if (index < 0 || index > N)
	  {
	    //std::cout << "Ignoring value not in range." << std::endl;
	    		throw BAD_CDF_ARGUMENT_OUT_OF_RANGE;
	    return;
	  }
	counts[index]++;
	count++;
}




void Cdf::sum()
{
	if (summed)
		return;

	int sum = 0;
	for (int i=0;i<N;i++)
	{
		sum += counts[i];
		F[i] = sum / (double) count;
	}

	summed = true;
}

void Cdf::debug()
{
	for (int i=0;i<N;i++)
	{
		std::cout << (lower + i / (double) N) << ":" << counts[i] << '\n';
	}
	std::cout << std::endl;
}


void Cdf::print(const char *filename, const std::string& name)
{
    std::ofstream outstr;
    outstr.open(filename);
    
    outstr << std::scientific << std::setprecision (std::numeric_limits<double>::digits10 + 1);
    
    outstr << "x_" << name << " = [";
    for (int i=0;i<N;i++)
	outstr << (lower + i / (double) N) << " ";
    outstr << "];\n";
    
    outstr << "y_prob_" << name << " = [";
    for (int i=0;i<N;i++)
	outstr << counts[i] / (double) count << " ";
    outstr << "];\n";
    
    sum();
    
    outstr << "y_cdf_" << name << " = [";
    for (int i=0;i<N;i++)
	outstr << F[i] << " ";
    outstr << "];\n";
    
    outstr << "plot(x_" << name << ", y_cdf_" << name << ");\n";
    
    outstr.close();
    
}
