#include <iostream>
#include "h.h"
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

void multigridTest()
{
	systemOfEquations sys;
	sys = ReadDrSaniFormat();
	cout << "Enter number of iterations for Gauss Seidel: ";
	int iter;
	cin >> iter;
	double* x_real = sys.x;
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

int main()
{
	multigridTest();
	/*matrix2D mat = Receive2Dmatrix();
	matrix2D mat2 = Receive2Dmatrix();
	double** result = multiplyMatrix(mat.A, mat.i, mat.j, mat2.A, mat2.j);
	for (int i = 0; i < mat.i; i++)
	{
		for (int j = 0; j < mat2.j; j++)
		{
			cout << result[i][j] << "\t";
		}
		cout << endl;
	}*/
	return 0;
}