#pragma once
struct matrix2D
{
	double** A;
	int i;
	int j;
};
struct CRS
{
	double* val;
	int* col_index;
	int* row_ptr;
	int nnz;
	int rows;
};
struct systemOfEquations
{
	double** A;
	double* b;
	double* x;
	int numOfEquations;
};
struct Coarse
{
	double** ACoarse; // A interpolated on coarse grid
	double* rCoarse; // Residual interpolated on coarse grid
	unsigned int noOfCoarseNodes;
	double** prolongation;
};
systemOfEquations ReceiveMatrices();
double* GuassSeidel(systemOfEquations sys, int iterations);
systemOfEquations ReadDrSaniFormat();
double* SolveWithAMG(systemOfEquations sys);
CRS* convertToCRS(double** const A, int row, int column);
double** multiplyMatrix(double** const A, int iA, int jA, double** const B, int jB);
matrix2D Receive2Dmatrix();