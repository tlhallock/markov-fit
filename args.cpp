
#include "args.h"

#include "constants.h"

#include <random>
#include <fstream>
#include <iomanip>



Args::Args(int n) :
  n{n},
  probs{new double[n*n]},
  lambdas{new double[n]}
  {
    if (n <= 0)
        throw ARGUMENT_INIT_ERROR;
  }

Args::Args(const char *filename)
{
	n = 0;
	std::ifstream instr(filename);
	instr >> n;
	probs = new double[n * n];
	lambdas = new double[n];
	for (int i = 0; i < n; i++)
		instr >> lambdas[i];
	for (int i = 0; i < n * n; i++)
		instr >> probs[i];

	instr.close();
}

Args::~Args()
{
	delete[] probs;
	delete[] lambdas;
}

bool Args::feasible() const
{
	return false;
}

void Args::randomize(double wait)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> unif1(0,  1);

	for (int i=0;i<n;i++)
	{
		for (int j=0;j<n;j++)
		{
			if (i==j)
				set_prob(i, j, 0);
			else
				set_prob(i, j, unif1(gen));
		}
	}
        
	for (int i=0;i<n;i++)
		lambdas[i] = wait * unif1(gen);

	normalize();
}

void Args::normalize()
{
	for (int i = 0; i < n; i++)
	{
		double sum = 0;
		for (int j = 0; j < n; j++)
		{
			sum += get_prob(i, j);
		}
		for (int j = 0; j < n; j++)
		{
			set_prob(i, j, get_prob(i, j) / sum);
		}
	}
}

void Args::write(const char *filename)
{
    std::ofstream outstr;
    outstr.open(filename);
    
    outstr << std::scientific << std::setprecision (std::numeric_limits<double>::digits10 + 1);
    
    outstr << n << "\n\n";
    for (int i=0;i<n;i++)
        outstr << lambdas[i] << ' ';
    outstr << "\n\n";
    
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
            outstr << probs[n * i + j] << ' ';
        outstr << '\n';
    }
    
    outstr.close();
    

}

Args& Args::operator =(const Args& other)
{
	if (get_size() != other.get_size())
		throw SIZE_MISMATCH_IN_MARKOV_ASSIGN;

	for (int i=0;i<n;i++)
		for (int j=0;j<n;j++)
			set_prob(i,j, other.get_prob(i, j));
	for (int i=0;i<n;i++)
		set_lambda(i,other.get_lambda(i));

	return *this;
}
