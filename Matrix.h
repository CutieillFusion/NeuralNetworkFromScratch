#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>

class Matrix
{
public:
	//Constructors
	Matrix();
	Matrix(unsigned rowSize, unsigned colSize, double initial);
	Matrix(const char* fileName);
	Matrix(const Matrix& matrix);
	~Matrix();

	//Helper Methods
	double& operator()(const unsigned& row, const unsigned& col);
	void Copy(Matrix& matrix);
	void Print() const;
	unsigned GetRows() const;
	unsigned GetCols() const;

	//Matrix Operators
	Matrix operator+(Matrix& B);
	Matrix operator-(Matrix& B);
	Matrix operator*(Matrix& B);
	Matrix Transpose();

	//Scalar Operators
	Matrix operator+(double scalar);
	Matrix operator-(double scalar);
	Matrix operator*(double scalar);
	Matrix operator/(double scalar);

private:
	unsigned rowSize;
	unsigned colSize;
	std::vector<std::vector<double>> matrix;
};

