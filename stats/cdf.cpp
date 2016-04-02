
#include "stats/cdf.h"
#include "constants.h"

#include <iomanip>
#include <fstream>
#include <limits>
#include <cmath>

Cdf::Cdf(const Stencil& stencil) :
	cached{stencil},
	count{0},
	counts{new int[stencil.N+1]},
	summed{false}
{
	reset();
}



Cdf::~Cdf()
{
	delete[] counts;
}

void Cdf::reset()
{
  for (int i=0;i<cached.bounds().N;i++)
    counts[i] = 0;
  count = 0;
  summed = false;
}

void Cdf::merge(const Cdf& other)
{
	if ( !(cached.bounds() == other.cached.bounds()))
		throw BAD_CDF_MERGE_EXCEPTION;
	
	for (int i=0;i<cached.bounds().N;i++)
		counts[i] += other.counts[i];

	count += other.count;
}

double Cdf::compare(Cdf& other)
{
	sum(); other.sum();
	return cached.compare(other.cached);
}

void Cdf::sample(const double value)
{
	summed = false;
	count++;

	if (value < cached.bounds().lower || value > cached.bounds().upper)
	{
		return;
	}

	int index = cached.bounds().map(value);
//	std::cout << value << " = " << index << std::endl;
	if (index < 0 || index > cached.bounds().N)
	{
		throw BAD_CDF_ARGUMENT_OUT_OF_RANGE;
	}
	counts[index]++;
}




void Cdf::sum()
{
	if (summed)
		return;

	int sum = 0;
	for (int i=0;i<cached.bounds().N;i++)
		cached.set(i, (sum += counts[i]) / (double) count);

	summed = true;
}


void Cdf::print(const char *filename, const std::string& name)
{
    std::ofstream outstr;
    outstr.open(filename);
    
    outstr << std::scientific << std::setprecision (std::numeric_limits<double>::digits10 + 1);
    
    outstr << "x_" << name << " = [";
    for (int i=0;i<cached.bounds().N;i++)
	outstr << cached.bounds().unmap(i) << " ";
    outstr << "];\n";
    
    outstr << "y_prob_" << name << " = [";
    for (int i=0;i<cached.bounds().N;i++)
	outstr << counts[i] / (double) count << " ";
    outstr << "];\n";
    
    sum();
    
    outstr << "y_cdf_" << name << " = [";
    for (int i=0;i<cached.bounds().N;i++)
	outstr << cached.get(i) << " ";
    outstr << "];\n";
    
    outstr << "plot(x_" << name << ", y_cdf_" << name << ");\n";
    
    outstr.close();
    
}


double Cdf::get_moment(int moment) const
{
	double sum = 0;
	for (int i=0;i<cached.bounds().N;i++)
	{
		sum += std::pow(cached.bounds().unmap(i), moment) * (counts[i] / (double) count);
	}
	return sum;
}


Cdf& Cdf::operator=(const Cdf& other)
{
	if (!(cached.bounds() == other.cached.bounds()))
		throw -1;

	for (int i=0;i<cached.bounds().N;i++)
		counts[i] = other.counts[i];
	count = other.count;
	if (other.summed)
	{
		cached = other.cached;
		summed = true;
	}
	else
	{
		summed = false;
	}
	return *this;
}

const SummedCdf& Cdf::getCdf()
{
	sum();
	return cached;
}

void SummedCdf::print(const char* filename, const char* name) const
{
	    std::ofstream outstr;
	    outstr.open(filename);

	    outstr << std::scientific << std::setprecision (std::numeric_limits<double>::digits10 + 1);

	    outstr << "x_" << name << " = [";
	    for (int i=0;i<stencil.N;i++)
		outstr << stencil.unmap(i) << " ";
	    outstr << "];\n";

	    outstr << "y_cdf_" << name << " = [";
	    for (int i=0;i<stencil.N;i++)
		outstr << F[i] << " ";
	    outstr << "];\n";

	    outstr << "plot(x_" << name << ", y_cdf_" << name << ");\n";

	    outstr.close();
}
//	    std::cout << "Ignoring value not in range." << std::endl;
//	    throw BAD_CDF_ARGUMENT_OUT_OF_RANGE;
