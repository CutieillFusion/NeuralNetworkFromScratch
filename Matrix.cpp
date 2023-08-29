#include "Matrix.h"

Matrix::Matrix()
{
	rowSize = 0;
	colSize = 0;
}

Matrix::Matrix(unsigned rowSize, unsigned colSize, double initial) : rowSize(rowSize), colSize(colSize)
{
	matrix.resize(rowSize);
	for (unsigned i = 0; i < matrix.size(); i++) 
	{
		matrix[i].resize(colSize, initial);
	}
}

Matrix::Matrix(const Matrix& matrix)
{
	rowSize = matrix.GetRows();
	colSize = matrix.GetCols();
	this->matrix.resize(rowSize);

	for (unsigned i = 0; i < this->matrix.size(); i++)
	{
		this->matrix[i].resize(colSize, 0.0);
	}

	unsigned i, j;
	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < colSize; j++)
		{
			this->matrix[i][j] = matrix.matrix[i][j];
		}
	}
}

Matrix::~Matrix()
{
}

Matrix Matrix::operator+(Matrix& B)
{
	Matrix sum (rowSize, colSize, 0.0);
	unsigned i, j;
	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < colSize; j++)
		{
			sum(i,j) = matrix[i][j] + B(i, j);
		}
	}
	return sum;
}

Matrix Matrix::operator-(Matrix& B)
{
	Matrix diff (rowSize, colSize, 0.0);
	unsigned i, j;
	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < colSize; j++)
		{
			diff.matrix[i][j] = matrix[i][j] - B.matrix[i][j];
		}
	}
	return diff;
}

Matrix Matrix::operator*(Matrix& B)
{
	Matrix mult (rowSize, B.GetCols(), 0.0);
	if(colSize == B.GetRows())
	{
		unsigned i, j, k;
		double temp;
		for (i = 0; i < rowSize; i++)
		{
			for (j = 0; j < B.GetCols(); j++)
			{
				temp = 0.0;
				for (k = 0; k < colSize; k++) 
				{
					temp += matrix[i][k] * B.matrix[k][j];
				}
				mult.matrix[i][j] = temp;
			}
		}
		return mult;
	}
	else 
	{
		std::cout << "ERROR MATRIX * OPERATOR" << std::endl;
		return mult;
	}
}


Matrix Matrix::Transpose()
{
	Matrix transpose(colSize, rowSize, 0.0);
	unsigned i, j;
	for (i = 0; i < colSize; i++)
	{
		for (j = 0; j < rowSize; j++) {
			transpose.matrix[i][j] = this->matrix[j][i];
		}
	}
	return transpose;
}

Matrix Matrix::operator+(double scalar)
{
	Matrix result(rowSize, colSize, 0.0);

	unsigned i, j;
	for (i = 0; i < rowSize; i++) 
	{
		for (j = 0; j < colSize; j++) 
		{
			result.matrix[i][j] = matrix[i][j] + scalar;
		}
	}
	return result;
}

Matrix Matrix::operator-(double scalar)
{
	Matrix result(rowSize, colSize, 0.0);

	unsigned i, j;
	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < colSize; j++)
		{
			result.matrix[i][j] = matrix[i][j] - scalar;
		}
	}
	return result;
}

Matrix Matrix::operator*(double scalar)
{
	Matrix result(rowSize, colSize, 0.0);

	unsigned i, j;
	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < colSize; j++)
		{
			result.matrix[i][j] = matrix[i][j] * scalar;
		}
	}
	return result;
}

Matrix Matrix::operator/(double scalar)
{
	Matrix result(rowSize, colSize, 0.0);

	unsigned i, j;
	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < colSize; j++)
		{
			result.matrix[i][j] = matrix[i][j] / scalar;
		}
	}
	return result;
}

double& Matrix::operator()(const unsigned& row, const unsigned& col)
{
	return matrix[row][col];
}

void Matrix::Copy(Matrix& matrix)
{
	rowSize = matrix.GetRows();
	colSize = matrix.GetCols();
	this->matrix.resize(rowSize);

	for (unsigned i = 0; i < this->matrix.size(); i++)
	{
		this->matrix[i].resize(colSize, 0.0);
	}

	unsigned i, j;
	for (i = 0; i < rowSize; i++)
	{
		for (j = 0; j < colSize; j++)
		{
			this->matrix[i][j] = matrix.operator()(i, j);
		}
	}
}
void Matrix::Print() const
{
	std::cout << "Matrix: " << std::endl;
	for (unsigned i = 0; i < rowSize; i++) {
		for (unsigned j = 0; j < colSize; j++) {
			std::cout << "[" << matrix[i][j] << "] ";
		}
		std::cout << std::endl;
	}
}

unsigned Matrix::GetRows() const
{
	return this->rowSize;
}

unsigned Matrix::GetCols() const
{
	return this->colSize;
}
