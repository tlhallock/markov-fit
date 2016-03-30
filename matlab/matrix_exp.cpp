//
//
//#include "matrix_exp.h"
//
//#include "engine.h"
//
//#include <iostream>
//#include <sstream>
//
//
//
//	Matlab::Matlab()
//	{
//		if (!(engine = engOpen("")))
//		{
//			std::cout << "Unable to start matlab." << std::endl;
//			throw 616;
//		}
//	}
//	Matlab::~Matlab()
//	{
//		if (engine != nullptr)
//			engClose((Engine *) engine);
//	}
//
//
//
//
//	double Matlab::get_hitting_time(Generator& generator)
//	{
//
//    int n = generator.get_size();
//
//    mxArray *Q = mxCreateDoubleMatrix(n-1, n-1, mxREAL);
//    double *vals = mxGetPr(Q);
//    for (int i=0;i<n-1;i++)
//	    for (int j=0;j<n-1;j++)
//		    vals[i + (n-1) * j] = generator.get_prob(i, j);
//
//    engPutVariable((Engine *) engine, "Q", Q);
//
//    std::stringstream cmd;
//    cmd << "p = [1 zeros(1, " << (n-2) << ")] * (Q \\ ones(" << (n-1) << ", 1));";
//    engEvalString((Engine *) engine, cmd.str().c_str());
//    mxArray *A = engGetVariable((Engine *) engine, "p");
//
//    vals = mxGetPr(A);
//	for (int i=0;i<1;i++)
//	{
//		std::cout << vals[i] << std::endl;
//	}
//
//	mxDestroyArray(Q);
//	mxDestroyArray(A);
//}
//
//
//
//
//
//
//
//
//
//
//
//
///*
//
//
//
//Engine *ep = nullptr;
//
//
//void test_engine()
//{
//    if (ep != nullptr)
//    {
//        return;
//    }
//
//    engine_lock.lock();
//    if (ep == nullptr)
//    {
//    }
//    engine_lock.unlock();
//}
//
//
//
//void matrix_exp(int n, double *matrix, double *times, double *output)
//{
//    test_engine();
//
//    mxArray *Q = mxCreateDoubleMatrix(3, 3, mxREAL);
//    double *vals = mxGetPr(Q);
//    vals[0] = 1;
//    vals[1] = 2;
//    vals[2] = 3;
//    vals[3] = 4;
//    vals[4] = 5;
//    vals[5] = 6;
//    vals[6] = 7;
//    vals[7] = 8;
//    vals[8] = 1;
//
//    engPutVariable(ep, "Q", Q);
//    engEvalString(ep, "A = exp(Q);");
//    mxArray *A = engGetVariable(ep, "A");
//
//    vals = mxGetPr(A);
//    for (int i=0;i<9;i++)
//    {
//        std::cout << vals[i] << std::endl;
//    }
//
//    mxDestroyArray(Q);
//    mxDestroyArray(A);
//}
//
//
//
//double get_hitting_time(Generator& generator)
//{
//}
//
//
//
//}
//
//
//void quit()
//{
//    engine_lock.lock();
//    engine_lock.unlock();
//}
//
//
//int main(int argc, char **argv)
//{
//    matrix_exp(0, nullptr, nullptr, nullptr);
//
//    quit();
//    return 0;
//}
//*/
