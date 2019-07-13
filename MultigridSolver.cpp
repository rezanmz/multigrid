#include "h.h"
#include <iostream>
using namespace std;
Coarse FindCoarse(int n, double** const A, double* const r)
{
	enum status { coarse, fine, none };
	status* s = new status[n];
	for (int i = 0; i < n; i++) s[i] = none;
	// Coarse and Fine points
	unsigned int coarseCount = 0;
	for (int i = 0; i < n; i++)
		if (s[i] == none)
		{
			s[i] = coarse;
			coarseCount++;
			for (int j = 0; j < n; j++)
				if (A[i][j] && s[j] == none)
				{
					s[j] = fine;
				}
		}
	int* coarseNode = new int[coarseCount];
	int index = 0;
	for (int i = 0; i < n; i++)
		if (s[i] == coarse)
		{
			coarseNode[index] = i;
			index++;
		}
	cout << "Coarse and Fine nodes were found!\n";

	// Prolongation operator
	double** p = new double* [n];
	for (int i = 0; i < n; i++) p[i] = new double[coarseCount];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < coarseCount; j++)
		{
			if (i == j)
			{
				p[i][j] = 0;
				continue;
			}
			if (s[i] == fine && A[i][coarseNode[j]])
			{
				int sigma = 0;
				for (int k = 0; k < n; k++)
					if (A[i][k] && i != k) sigma++;
				p[i][j] = 1 / (double)sigma;
			}
			else p[i][j] = 0;
		}

	delete[] s;
	delete[] coarseNode;
	cout << "Prolongation operator was created!\n";

	// Interpolating A to coarse grid
	Coarse c;
	c.ACoarse = new double* [coarseCount];
	for (int i = 0; i < coarseCount; i++) c.ACoarse[i] = new double[coarseCount];
	c.rCoarse = new double[coarseCount];

	// Finding p_transposed
	double** p_transposed = new double* [coarseCount];
	for (int i = 0; i < coarseCount; i++) p_transposed[i] = new double[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < coarseCount; j++)
			p_transposed[j][i] = p[i][j];
	cout << "p transposed was calculated.\n";

	// Calculating p_transposed*A
	double** temp = new double* [coarseCount];
	for (int i = 0; i < coarseCount; i++) temp[i] = new double[n];

	for (int i = 0; i < coarseCount; i++)
		for (int j = 0; j < n; j++)
		{
			temp[i][j] = 0;
			for (int k = 0; k < n; k++)
				temp[i][j] += p_transposed[i][k] * A[k][j];
		}
	cout << "p_transposed*A was calculated.\n";
	// Calculating ACoarse = p_transposed*A*p
	for (int i = 0; i < coarseCount; i++)
		for (int j = 0; j < coarseCount; j++)
		{
			c.ACoarse[i][j] = 0;
			for (int k = 0; k < n; k++)
				c.ACoarse[i][j] += temp[i][k] * p[k][j];
		}
	delete[] temp;
	cout << "'A' was interpoolated to coarse grid.\n";


	// Interpolating r to coarse grid
		// Calculating rCoarse = p_transposed*r
	for (int i = 0; i < coarseCount; i++)
	{
		c.rCoarse[i] = 0;
		for (int j = 0; j < n; j++)
			c.rCoarse[i] += p_transposed[i][j] * r[j];
	}

	c.noOfCoarseNodes = coarseCount;
	c.prolongation = p;
	cout << "'r' was interpolated to coarse grid.";

	return c;
}

double* SolveWithAMG(systemOfEquations sys)
{
	double** A = sys.A;
	double* b = sys.b;
	double* x = sys.x;
	int n = sys.numOfEquations;
	// Calculate residual on fine grid -> b-Au=r
	double* r = new double[n];
	for (int i = 0; i < n; i++)
	{
		double sum = 0;
		for (int j = 0; j < n; j++)
		{
			sum += A[i][j] * x[j];
		}
		r[i] = b[i] - sum;
	}
	cout << "Residual 'r' was calculated on fine grid.\n";
	// Finding coarse grid
	Coarse c = FindCoarse(n, A, r);

	// Calculating 'e' on coarse grid Ae=r
	systemOfEquations eInCoarseGrid;
	eInCoarseGrid.A = c.ACoarse;
	eInCoarseGrid.b = c.rCoarse;
	eInCoarseGrid.numOfEquations = c.noOfCoarseNodes;
	double* eCoarse = GuassSeidel(eInCoarseGrid, 10);
	cout << "Error 'e' was calculated on coarse grid.\n";

	// Interpolating 'e' to fine grid ... p*e
	double* e = new double[n];
	for (int i = 0; i < n; i++)
	{
		e[i] = 0;
		for (int j = 0; j < c.noOfCoarseNodes; j++)
			e[i] += c.prolongation[i][j] * eCoarse[j];
	}
	delete[] eCoarse;
	cout << "Error 'e' was interpolated back to fine grid.";

	// Adding 'e' to approximate 'x' to achieve a better answer
	for (int i = 0; i < n; i++)
		x[i] += e[i];
	delete[] e;

	for (int i = 0; i < c.noOfCoarseNodes; i++)
		delete[] c.ACoarse[i];
	delete[] c.ACoarse;
	delete[] c.rCoarse;
	return x;
}