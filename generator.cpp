
#include "generator.h"

#include "constants.h"

#include <random>
#include <fstream>
#include <iomanip>
#include <cmath>



Generator::Generator(int n) :
  n{n},
  probs{new double[n*n]}
  {
    if (n <= 0)
        throw GENERATOR_INIT_ERROR;
  }
  
  

Generator::Generator(const char *filename)
{
	std::ifstream instr(filename);

	instr >> n;

	probs = new double[n * n];
	for (int i = 0; i < n * n; i++)
		instr >> probs[i];

	instr.close();
}



Generator::Generator(const Args& markov) :
		n{markov.get_size()},
		probs{new double[n*n]}

{
	for (int r=0;r<n;r++)
	{
		const double lambda = markov.get_lambda(r);
		double sum = 0.0;

		for (int c=0; c<n; c++)
		{
			if (c == r)
				continue;
			double q = lambda * markov.get_prob(r, c);
			set_prob(r, c, q);
			sum += q;
		}

		set_prob(r, r, -sum);
	}
}

/**
 * Doesn't handle non-communicating states...
 */
void Generator::assign(Args& markov) const
{
	for (int r=0;r<n;r++)
	{
		double sum = 0;
		for (int c=0; c<n; c++)
		{
			if (get_prob(r, c) < 0)
				markov.set_lambda(c, -get_prob(r, c));
			else
				sum += get_prob(r, c);
		}

		for (int c=0; c<n; c++)
		{
			if (c == r)
				markov.set_prob(r, c, 0);
			else
				markov.set_prob(r, c, get_prob(r, c) / sum);
		}
	}
}


Generator::~Generator()
{
  delete[] probs;
}

void Generator::randomize(double var)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> d(0,var);
	for (int i=0;i<n*n;i++)
	{
		probs[i] = d(gen);
		// oops, not what I meant... (should change distro)
		if (probs[i] < 0)
			probs[i] = -probs[i];
	}
	
	normalize();
}

void Generator::randomize(std::mt19937& gen, std::normal_distribution<>& dist)
{
	for (int i=0;i<n*n;i++)
	{
		probs[i] = dist(gen);
		// oops, not what I meant... (should change distro)
		if (probs[i] < 0)
			probs[i] = -probs[i];
	}

	normalize();
}

void Generator::normalize()
{
	for (int i = 0; i < n; i++)
	{
		double sum = 0;
		for (int j = 0; j < n; j++)
		{
			if (i == j)
				continue;
			sum += get_prob(i, j);
		}

		set_prob(i, i, -sum);
	}
}


void Generator::write(const char *filename)
{
    std::ofstream outstr;
    outstr.open(filename);
    outstr << std::scientific << std::setprecision (std::numeric_limits<double>::digits10 + 1);
    
    outstr << n << "\n\n";
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
            outstr << probs[n * i + j] << ' ';
        outstr << '\n';
    }
    
    
    outstr.close();
    
}
void Generator::writeMatlab(const char *filename)
{
    
    std::ofstream outstr;
    outstr.open(filename);
    outstr << std::scientific << std::setprecision (std::numeric_limits<double>::digits10 + 1);
    
    outstr << "\n\n Q = [ ";
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
            outstr << probs[n * i + j] << ' ';
        outstr << ";...\n";
    }
    outstr << "];\n";
    
    outstr.close();
}

double Generator::get_distance(const Generator& other) const
{
	double sum = 0.0;

	for (int r=0; r<n; r++)
	{
		double debug = 0.0;
		for (int c=0;c<n;c++)
		{
			if (r==c)
				continue;
			double d = get_prob(r, c) - other.get_prob(r, c);
			sum += d*d;
			debug += d*d;
		}
	}

	return sum / get_size();
}

Generator& Generator::operator =(const Generator& other)
{
	if (get_size() != other.get_size())
		throw SIZE_MISMATCH_IN_MARKOV_ASSIGN;
	for (int r=0; r<n; r++)
		for (int c=0;c<n;c++)
			set_prob(r, c, other.get_prob(r, c));
	return *this;
}

void Generator::set_radius_from(const Generator& other, double radius)
{
	for (int r=0;r<n;r++)
	{
		double sum1 = 0.0;
		for (int c=0;c<n;c++)
		{
			if (r==c)
				continue;
			double d = get_prob(r, c) - other.get_prob(r, c);
			sum1 += d*d;
		}

		sum1 = std::sqrt(sum1);

		double sum2 = 0.0;
		for (int c=0;c<n;c++)
		{
			double q = other.get_prob(r, c) + (get_prob(r, c) - other.get_prob(r, c)) / sum1;
			if (q < 0) q = 0;
			set_prob(r, c, q);
			sum2 = q;
		}
		set_prob(r, r, -sum2);
	}
}
