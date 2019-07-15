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
	crs->row_ptr[row] = crs->nnz + 1;
	return crs;
}