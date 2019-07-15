#include <iostream>
#include "h.h"
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
int main()
{
	


	systemOfEquations sys;
	sys = ReadDrSaniFormat();
	cout << "Enter number of iterations for Gauss Seidel: ";
	int iter;
	cin >> iter;
	double* x_real=sys.x;
	sys.x = GuassSeidel(sys, iter);


	double norm2 = 0;
	for (int i = 0; i < sys.numOfEquations; i++)
		norm2 += (x_real[i] - sys.x[i]) * (x_real[i] - sys.x[i]);
	norm2 = sqrt(norm2) / sys.numOfEquations;
	cout << "After smoother (norm2 of X_real-X_approximate)\n: " << norm2;


	sys.x = SolveWithAMG(sys);
	norm2 = 0;
	for (int i = 0; i < sys.numOfEquations; i++)
		norm2 += (x_real[i] - sys.x[i]) * (x_real[i] - sys.x[i]);
	norm2 = sqrt(norm2) / sys.numOfEquations;
	cout << "After multigrid(norm2 of X_real-X_approximate)\n: " << norm2;
}