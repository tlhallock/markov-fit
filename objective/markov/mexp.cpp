/*
 * mexp.cpp
 *
 *  Created on: Apr 1, 2016
 *      Author: default
 */

#include "markov/mexp.h"

#include "gsl/gsl_linalg.h"




GslContext::GslContext(int n) :
	n{n},
	m1{gsl_matrix_alloc(n-1, n-1)},
	m2{gsl_matrix_alloc(n-1, n-1)} {}

GslContext::~GslContext()
{
	gsl_matrix_free((gsl_matrix *)m1);
	gsl_matrix_free((gsl_matrix *)m2);
}













//double mat_exp_3_5(const double *const q);
//#include <iostream>



void set_cdf(const Generator& gen, SummedCdf& cdf, GslContext& context)
{
	gsl_matrix *A = (gsl_matrix *) context.get_input();
	gsl_matrix *B = (gsl_matrix *) context.get_output();

	const Stencil& bounds = cdf.bounds();

	const int n = context.get_size();


//	if (gen.get_size() != 4) throw 1;

//	double *test_q = new double[(n-1) * (n-1)];

	for (int i=0;i<bounds.N;i++)
	{
		double t = bounds.unmap(i);

		for (int j=0;j<n-1;j++)
			for (int k=0;k<n-1;k++)
			{
				gsl_matrix_set(A, j, k, gen.get_prob(j, k) * t);
//				test_q[j * (n-1) + k] = gen.get_prob(j, k) * t;
			}

		gsl_linalg_exponential_ss(A, B, GSL_PREC_DOUBLE);

		double d = 0;
		for (int j=0;j<n-1;j++)
			d += gsl_matrix_get(B, 0, j);

//		std::cout << "x            =" << t << std::endl;
//		std::cout << "d            =" << d << std::endl;
//		std::cout << "approximation=" << mat_exp_3_5(test_q) << std::endl;
//		std::cout << std::endl;

		cdf.set(i, 1-d);
	}

//	delete test_q;
}




//	gsl_matrix *left = gsl_matrix_alloc(1, n-1);
//	gsl_matrix *right = gsl_matrix_alloc(n-1, 1);
//	gsl_matrix_set_all(right, 1);
//	gsl_matrix_set_zero(left);
//	gsl_matrix_set(left, 0, 0, 1);

//	gsl_matrix_set(A, 0, 0,  -1);
//	gsl_matrix_set(A, 0, 1,  .5);
//	gsl_matrix_set(A, 0, 2,  .5);
//
//	gsl_matrix_set(A, 1, 0, 1.5);
//	gsl_matrix_set(A, 1, 1,  -2);
//	gsl_matrix_set(A, 1, 2,  .5);
//
//	gsl_matrix_set(A, 2, 0,   0);
//	gsl_matrix_set(A, 2, 1,   1);
//	gsl_matrix_set(A, 2, 2,  -1);

//	gsl_matrix_fprintf(stdout, A, "%g");
//	gsl_matrix_fprintf(stdout, B, "%g");

