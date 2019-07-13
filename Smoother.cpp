#include "h.h"
#include <iostream>
using namespace std;
double* GuassSeidel(systemOfEquations sys, int iterations)
{
	double* guess = new double[sys.numOfEquations];
	for (int i = 0; i < sys.numOfEquations; i++)
		guess[i] = 0;
	for (int iter = 0; iter < iterations; iter++)
	{
		for (int i = 0; i < sys.numOfEquations; i++)
		{
			double sum = 0;
			for (int j = 0; j < sys.numOfEquations; j++)
			{
				if (i == j) continue;
				sum += sys.A[i][j] * guess[j];
			}
			guess[i] = (sys.b[i] - sum) / sys.A[i][i];
		}
		cout << "current iter: " << iter << endl;
	}
	return guess;
}