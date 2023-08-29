#pragma once
#include "Matrix.h"
#include "CSVParser.h"
#include <math.h>

const double EulerNum = 2.7182818284590452353602874713527;

#define DEBUG(x) std::cout << x << std::endl

class AI
{
public:
	AI(Matrix X, Matrix Y);
	~AI();

	void GradientDescent(int iterations);
protected:
	void InitializeWeightsAndBiases();
	void GetCurrentX(int index);
	Matrix ReLU(Matrix& X);
	Matrix Softmax(Matrix& X);
	void ForwardPropagation();
	Matrix OneHot(Matrix& Y);
	Matrix ReLUDerivative(Matrix& Z);
	void BackwardsPropagation();
	void UpdateParameters(float alpha);
	int GetPredictions(Matrix& A2);
	double GetAccuracy();
private:
	Matrix Z1, Z2, W1, W2, b1, b2;
	Matrix dZ1, dZ2, dW1, dW2, db1, db2;
	Matrix XCol, X, Y, A1, A2;
	std::vector<int> predictions;
	float alpha = 0.1f;
};

