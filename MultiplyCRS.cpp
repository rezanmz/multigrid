#include "h.h"
#include <iostream>
// Since jA and iB are the same, we only receive one parameter for both
double** multiplyMatrix(double** const A, int iA, int jA, double** B, int jB)
{
	// Converting A to CRS
	CRS* crsA = convertToCRS(A, iA, jA);
	// Creating a matrix with the dimension iA*jB to hold the answer to the multiplication.
	double** result = new double* [iA];
	for (int i = 0; i < iA; i++) result[i] = new double[jB];
	for (int i = 0; i < iA; i++)
		for (int j = 0; j < jB; j++)
			result[i][j] = 0;

	for (int column = 0; column < jB; column++)
	{
		for (int i = 0; i < iA; i++)
		{
			for (int k = crsA->row_ptr[i]; k < crsA->row_ptr[i + 1]; k++)
			{
				result[i][column] += crsA->val[k] * B[crsA->col_index[k]][column];
			}
		}
	}
	delete crsA;
	return result;
}