#include "Naive.h"

Naive::Naive()
{
	Naive::tauA = 0;
}

Naive::~Naive()
{
}

/**
  Returns 1 if the sign is positive, -1 if negative, 0 otherwise
*/
int Naive::calc_sign(int v) {
	return (v > 0) - (v < 0);
}

/**
  Compares pairwise the joint elements in the two vectors
*/
void Naive::tauA_computation(vector<int> &u, vector<int> &v, int n) {
	int num = 0;
	#pragma omp parallel for reduction(+:num)
	for (int i = 0; i < n; i++) {
		int a = u[i];
		int b = v[i];
		for (int j = i + 1; j < n; j++) {
			num += calc_sign((a - u[j]) * (b - v[j]));
		}
	}
	double result = (double) num / (n*(n - 1) / 2);
	Naive::tauA = result;
}

/**
  Manages the steps of the algorithm
*/
void Naive::naive_algorithm(vector<int> &u, vector<int> &v, int n, int num_threads) {

#ifdef _OPENMP
	/* Set the number of threads */
	omp_set_num_threads(num_threads);
#endif

	double overall_start_clock = omp_get_wtime();
		
	Naive::tauA_computation(u, v, n);
	cout << "Kendall's tauA coefficient: " << Naive::tauA << endl;
	
	double overall_end_clock = omp_get_wtime();
	cout << "Overall time: " << overall_end_clock - overall_start_clock << endl;
	cout << endl;

	system("pause");
}
