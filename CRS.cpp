#include "h.h"
CRS* convertToCRS(double** const A, int row, int column)
{
	CRS* crs = new CRS{};

	crs->rows = row;
	crs->nnz = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			if (A[i][j]) crs->nnz++;
		}
	}
	crs->val = new double[crs->nnz];
	crs->col_index = new int[crs->nnz];
	crs->row_ptr = new int[row + 1];
	for (int i = 0; i < crs->nnz; i++) crs->val[i] = 0;
	for (int i = 0; i < crs->nnz; i++) crs->col_index[i] = 0;
	for (int i = 0; i < row + 1; i++) crs->row_ptr[i] = 0;

	int index = 0;
	bool firstInRow = true;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{

			if (A[i][j])
			{
				if (firstInRow) crs->row_ptr[i] = index;
				crs->val[index] = A[i][j];
				crs->col_index[index] = j;
				index++;
				firstInRow = false;
			}
		}
		firstInRow = true;
	}
	crs->row_ptr[row] = crs->nnz;
	return crs;
}

double** convertFromCRS(CRS* mat, int col)
{
	double** A = new double* [mat->rows];
	for (int i = 0; i < mat->rows; i++) A[i] = new double[col];
	for (int i = 0; i < mat->rows; i++)
		for (int j = 0; j < col; j++) A[i][j] = 0;
	int currRow = 0;
	for (int i = 0; i < mat->nnz; i++)
	{
		for (int j = 0; j < mat->rows; j++)
		{
			if (i >= mat->row_ptr[j] && i < mat->row_ptr[j + 1])
			{
				currRow = j;
				break;
			}
		}
		A[currRow][mat->col_index[i]] = mat->val[i];
	}
	return A;
}

// Since jA and iB are the same, we only receive one parameter for both
double** multiplyMatrix(double** const A, int iA, int jA, double** const B, int jB)
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

CRS* multiplyMatrixCRS(CRS* const A, int iA, int jA, CRS* const B, int jB)
{
	double** result = new double* [iA];
	for (int i = 0; i < iA; i++) result[i] = new double[jB];
	for (int i = 0; i < iA; i++)
		for (int j = 0; j < jB; j++)
			result[i][j] = 0;
	CRS* resultCRS = new CRS{};
	// Converting B from CRS
	double** matB = convertFromCRS(B, jB);

	for (int column = 0; column < jB; column++)
	{
		for (int i = 0; i < iA; i++)
		{
			for (int k = A->row_ptr[i]; k < A->row_ptr[i + 1]; k++)
			{
				result[i][column] += A->val[k] * matB[A->col_index[k]][column];
			}
		}
	}

	for (int i = 0; i < jA; i++)
		delete[] matB[i];
	delete[] matB;
	resultCRS = convertToCRS(result, iA, jB);
	for (int i = 0; i < iA; i++)
		delete[] result[i];
	delete[] result;
	return resultCRS;
}

CRS* transposeCRS(CRS* const mat)
{
	CRS* result = new CRS{};
	result->col_index = new int[mat->nnz];
	result->val = new double[mat->nnz];
	result->row_ptr = new int[mat->rows];
	result->rows = mat->rows;
	int* temp = new int[mat->nnz];
	unsigned int index = 0;
	int currRow = 0;
	for (int i = 0; i < mat->nnz; i++)
	{
		if (i < mat->row_ptr[currRow + 1])
		{
			temp[i] = currRow;
		}
		else
		{
			temp[i] = currRow + 1;
			currRow++;
		}
	}
	result->row_ptr = temp;
	for (int i = 0; i < mat->rows; i++)
	{
		for (int j = 0; j < mat->nnz; j++)
		{
			if (mat->col_index[j] == i)
			{
				result->val[index] = mat->val[j];
				result->col_index[index] = mat->col_index[j];
				int temp2 = temp[index];
				temp[index] = temp[j];
				temp[j] = temp2;
				index++;
			}
		}
	}
	index = 1;
	int prevVal = 0, currVal = 0;;
	temp = new int[mat->rows + 1];
	temp[0] = 0;
	for (int i = 0; i < mat->nnz; i++)
	{
		currVal = result->col_index[i];
		if (prevVal != currVal)
		{
			temp[index] = i;
			prevVal = currVal;
			index++;
		}
	}
	temp[mat->rows] = mat->nnz;
	delete[] result->col_index;
	result->col_index = result->row_ptr;
	result->row_ptr = temp;
	return result;
}