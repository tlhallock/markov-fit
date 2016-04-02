//
//#include <algorithm>    // std::random_shuffle
//#include <random>
//
//
//class LocalSearchParams
//{
//private:
//	int n;
//
//	int min_change;
//	int max_change;
//
//	int min_radius;
//	int max_radius;
//	double decrease;
//
//	int niter;
//	int ndec;
//
//	std::random_device rd;
//	std::mt19937 gen;
//	std::uniform_real_distribution<> unif;
//public:
//	LocalSearchParams(double r, int n) :
//		n{n},
//		min_change{1},
//		max_change{n*(n+1)},
//		min_radius{1},
//		max_radius{1e-7},
//		decrease{2},
//		niter{1000},
//		ndec{10},
//		rd{},
//		gen{rd()},
//		unif{0,1}
//	{
//
//	}
//
//	~LocalSearchParams() {}
//
//	void modify(Markov& markov)
//	{
//		int *idcs = new int[n * (n+1)];
//		for (int i=0;i<n*(n+1);i++)
//			idcs[i] = i;
//
//		double radius = max_radius;
//		for (int i=0;i<ndec;i++)
//		{
//			for (int j=0;j<niter;j++)
//			{
//				int num = (int) (min_change + unif(gen) * (max_change - min_change));
//				std::random_shuffle(&idcs[0], &idcs[n*(n+1)]);
//				for (int i=0;i<num;i++)
//				{
//
//				}
//			}
//
//			radius /= decrease;
//		}
//
//		delete[] idcs;
//	}
//};
//
//
//void local_search(Markov& orig, Markov& muta, Markov& scratch, LocalSearchParams& params)
//{
//
//
//}
