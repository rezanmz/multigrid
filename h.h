#pragma once
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
CRS* multiplyMatrix(double** A, int nA, double** B, int nB);