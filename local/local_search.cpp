/*
 * local_search.cpp
 *
 *  Created on: Mar 29, 2016
 *      Author: default
 */


#include "local/local_search.h"

#include "markov/generator.h"
#include "markov/mexp.h"

#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>



void local_search(Markov& original, Markov& result, LocalGeneticSearchParams& params)
{
//	Generator ** pop = new Generator*[params.get_pop_size()];
//	for (int i=0;i<params.get_pop_size(); i++)
//	{
//		pop[i] = new Generator{original.get_n_states()};
//		pop[i]->randomize(1.0);
//	}
//
//
//
//	Generator gen2{args.get_size()};
//	gen2.randomize();
//
//	gen2.set_radius_from(generator, 1.0);




//
//
//	for (int i=0;i<params.get_pop_size(); i++)
//	{
//		delete chains[i];
//	}
//	delete[] chains;
}


void local_search_simple_expm(const SummedCdf& desired, Args& chain, int maxiters, double tol)
{
	const double TOLERANCE = 1e-3;

	// Create random devices...
	std::random_device rd;
	std::mt19937 gen{rd()};
	std::normal_distribution<> normal{0, 1};
	std::uniform_real_distribution<> unif{0, 1};

	// Create generators...
	Generator gen_optimal{chain};
	Generator gen_current{chain.get_size()};

	SummedCdf cdf_optimal {desired.bounds()};
	SummedCdf cdf_current {desired.bounds()};

	GslContext context{chain.get_size()};

	set_cdf(gen_optimal, cdf_optimal, context);


	Args test_chain{chain.get_size()};

	int improvement_count = 0;
	double current_distance = 1.0;
	double radius = 2;

	while (radius >= tol)
	{
		std::cout << "radius = " << radius << std::endl;

		int count_since_improved = 0;
		while (count_since_improved++ < maxiters)
		{
			gen_current.randomize(gen, normal);
			gen_current.set_radius_from(gen_optimal, radius);
			set_cdf(gen_current, cdf_current, context);

			double diff = cdf_current.compare(desired);
			if (diff >= current_distance)
			{
				continue;
			}

			std::cout << count_since_improved << " failed searches." << std::endl;

			current_distance = diff;
			gen_optimal = gen_current;
			count_since_improved = 0;
			chain = test_chain;

			improvement_count++;

			char name_buffer[256];
			char file_buffer[256];

			sprintf(name_buffer, "improvement_%d", improvement_count);
			sprintf(file_buffer, "output/improvement_%d.m", improvement_count);

			std::ofstream outfile;
			outfile.open(file_buffer);
			{
				outfile << std::scientific << std::setprecision(std::numeric_limits<double>::digits10 + 1);

				outfile << "x = [";
				for (int i = 0; i < desired.bounds().N; i++)
					outfile << desired.bounds().unmap(i) << " ";
				outfile << "];\n";

				outfile << "y_current_" << improvement_count << " = [";
				for (int i = 0; i < desired.bounds().N; i++)
					outfile << cdf_current.get(i) << " ";
				outfile << "];\n";

				outfile << "y_desired_" << improvement_count << " = [";
				for (int i = 0; i < desired.bounds().N; i++)
					outfile << desired.get(i) << " ";
				outfile << "];\n";

				outfile << "plot(x, y_current_" << improvement_count << ", x, y_desired_" << improvement_count << ");\n";
			}


			outfile.close();
		}

		radius /= 2;
	}

}


void local_search_simple_sim(Cdf& desired, Args& args, int maxiters, double tol)
{
	const double TOLERANCE = 1e-3;

	std::random_device rd;
	std::mt19937 gen{rd()};
	std::normal_distribution<> normal{0, 1};
	std::uniform_real_distribution<> unif{0, 1};

	Cdf cdf_optimal{desired};
	Cdf cdf_current{desired};
	Cdf cdf_tmp{desired};

	Markov simulator{args};
	simulator.simulate(cdf_optimal, cdf_tmp, TOLERANCE, gen, unif);

	Generator gen_optimal{args};
	Generator gen_current{args.get_size()};

	Args test_chain{args.get_size()};

	int improvement_count = 0;
	double current_distance = 1.0;
	double radius = 2;


	gen_optimal.writeMatlab("output/generator.m");
	cdf_optimal.print("output/gen_cdf.m", "gen_cdf");





	if (1)
		return;


	while (radius >= tol)
	{
		std::cout << "radius = " << radius << std::endl;

		int count_since_improved = 0;
		while (count_since_improved++ < maxiters)
		{
			cdf_current.reset();
			gen_current.randomize(gen, normal);
			gen_current.set_radius_from(gen_optimal, radius);
			gen_current.assign(test_chain);

			test_chain.write("output/current.txt");
			simulator = test_chain;



			simulator.simulate(cdf_current, cdf_tmp, TOLERANCE, gen, unif);

			double diff = cdf_current.compare(desired);
			if (diff >= current_distance)
			{
				continue;
			}

			std::cout << count_since_improved << " failed searches." << std::endl;

			current_distance = diff;
			gen_optimal = gen_current;
			count_since_improved = 0;
			args = test_chain;

			improvement_count++;

			char name_buffer[256];
			char file_buffer[256];

			sprintf(name_buffer, "improvement_%d", improvement_count);
			sprintf(file_buffer, "output/improvement_%d.m", improvement_count);

			cdf_current.print(file_buffer, name_buffer);

		}

		radius /= 2;
	}

}
