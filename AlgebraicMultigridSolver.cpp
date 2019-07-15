#include <iostream>
#include "h.h"
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
int main()
{
	double** A = new double* [6];
	for (int i = 0; i < 6; i++) A[i] = new double[6];
	A[0][0] = 10; A[0][1] = 0; A[0][2] = 0; A[0][3] = 0; A[0][4] = -2; A[0][5] = 0;
	A[1][0] = 3; A[1][1] = 9; A[1][2] = 0; A[1][3] = 0; A[1][4] = 0; A[1][5] = 3;
	A[2][0] = 0; A[2][1] = 7; A[2][2] = 8; A[2][3] = 7; A[2][4] = 0; A[2][5] = 0;
	A[3][0] = 3; A[3][1] = 0; A[3][2] = 8; A[3][3] = 7; A[3][4] = 5; A[3][5] = 0;
	A[4][0] = 0; A[4][1] = 8; A[4][2] = 0; A[4][3] = 9; A[4][4] = 9; A[4][5] = 13;
	A[5][0] = 0; A[5][1] = 4; A[5][2] = 0; A[5][3] = 0; A[5][4] = 2; A[5][5] = -1;
	CRS* crs = convertToCRS(A, 6, 6);
	cout << "val: ";
	for (int i = 0; i < crs->nnz; i++)
		cout << crs->val[i] << "\t";
	cout << endl << "col_index";
	for (int i = 0; i < crs->nnz; i++)
		cout << crs->col_index[i] << "\t";
	cout << endl << "row_ptr: ";
	for (int i = 0; i < crs->rows + 1; i++)
		cout << crs->row_ptr[i] << "\t";





	/*systemOfEquations sys;
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
	cout << "After multigrid(norm2 of X_real-X_approximate)\n: " << norm2;*/
}