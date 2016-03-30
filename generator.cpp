
#include "generator.h"

#include "constants.h"

#include <random>
#include <fstream>
#include <iomanip>



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
    
    probs = new double[n*n];
    for (int i=0;i<n * n;i++)
        instr >> probs[i];
    
    instr.close();
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
		probs[i] = d(gen);
	
	normalize();
}

void Generator::normalize()
{
  for (int i=0;i<n;i++)
    {
      double avg = 0;
    for (int j=0;j<n;j++)
      {
	avg += probs[n * i + j];
      }
      avg /= n;
    for (int j=0;j<n;j++)
      {
	probs[n * i + j] -= avg;
      }
    }
}



//Generator* read(const char *filename)
//{
//	return new Generator(filename);
//}

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
  