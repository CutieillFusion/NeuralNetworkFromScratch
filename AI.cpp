#include "AI.h"

AI::AI(Matrix X, Matrix Y) : X(X), Y(Y)
{
}

AI::~AI()
{
}

void AI::InitializeWeightsAndBiases()
{
	//Providing a seed value
	srand((unsigned)time(NULL));
	
	// Get a random number
	int random = rand();
	
	unsigned i, j;
	//Initialize W1
	for (i = 0; i < W1.GetRows(); i++) 
	{
		for (j = 0; j < W1.GetCols(); j++)
		{
			W1(i, j) = (rand() % 1000) / 1000.0;
		}
	}
	
	//Initialize b1
	for (i = 0; i < b1.GetRows(); i++)
	{
		for (j = 0; j < b1.GetCols(); j++)
		{
			b1(i, j) = (rand() % 1000) / 1000.0;
		}
	}
	
	//Initialize W2
	for (i = 0; i < W2.GetRows(); i++)
	{
		for (j = 0; j < W2.GetCols(); j++)
		{
			W2(i, j) = (rand() % 1000) / 1000.0;
		}
	}
	
	//Initialize b2
	for (i = 0; i < b2.GetRows(); i++)
	{
		for (j = 0; j < b2.GetCols(); j++)
		{
			b2(i, j) = (rand() % 1000) / 1000.0;
		}
	}
}

void AI::GetCurrentX(int index)
{
	XCol = Matrix(784, 1, 0.0);
	for (unsigned i = 0; i < X.GetRows(); i++) 
	{
		XCol(i, 0) = X(i, index);
	}
}

Matrix AI::ReLU(Matrix& X)
{
	Matrix ReLU = Matrix(X);
	unsigned i, j;
	for (i = 0; i < X.GetRows(); i++)
	{
		for (j = 0; j < X.GetCols(); j++)
		{
			ReLU(i, j) = std::fmax(0, X(i,j));
		}
	}
	return ReLU;
}

Matrix AI::Softmax(Matrix& X)
{
	Matrix softmax = Matrix(X);
	double sum = 0.0;
	unsigned i;
	for (i = 0; i < X.GetRows(); i++) 
	{
		sum += std::pow(EulerNum, softmax(i,0));
	}

	for (i = 0; i < X.GetRows(); i++)
	{
		softmax(i,0) = std::pow(EulerNum, softmax(i, 0)) / sum;
	}
	return softmax;
}

void AI::ForwardPropagation()
{
	b1.Print();
	Z1 = W1 * XCol + b1;
	Z1.Print();
	A1 = ReLU(Z1);
	Z2 = W2 * A1 + b2;
	A2 = Softmax(Z2);
}

Matrix AI::OneHot(Matrix& Y)
{
	Matrix OneHotY = Matrix(Y.GetRows(), 1, 0.0);
	unsigned i, maxIndex = 0;
	double maxNum = 0.0;
	for (i = 0; i < OneHotY.GetRows(); i++) 
	{
		if (Y(i, 0) > maxNum) 
		{
			maxNum = Y(i, 0);
			maxIndex = i;
		}
	}
	OneHotY(maxIndex, 0) = 1;
	OneHotY.Transpose();
	return OneHotY;
}

Matrix AI::ReLUDerivative(Matrix& Z1)
{
	Matrix ReLU = Matrix(Z1);
	unsigned i, j;
	for (i = 0; i < Z1.GetRows(); i++)
	{
		for (j = 0; j < Z1.GetCols(); j++)
		{
			ReLU(i, j) = (Z1(i, j) > 0);
		}
	}
	return ReLU;
}

void AI::BackwardsPropagation()
{
	Matrix oneHotY = OneHot(Y);
	Matrix dZ2 = A2 - oneHotY;
	Matrix A1Transposed = A1.Transpose();
	dW2 = dZ2 * A1Transposed * 1.0 / Y.GetRows();

	Matrix dZ2Sum = Matrix(dZ2.GetRows(), 1, 0.0);
	unsigned i, j;
	for (i = 0; i < dZ2.GetRows(); i++) 
	{
		for (j = 0; j < dZ2.GetCols(); j++)
		{
			dZ2Sum(i,0) += dZ2(i, j);
		}
	}

	db2 = dZ2Sum * (1.0 / Y.GetRows());
	Matrix Z1ReLUDerivative = ReLUDerivative(Z1);//Scalar Matrix
	Matrix dZ1 = W2 * dZ2;
	for (i = 0; i < dZ1.GetRows(); i++) 
	{
		dZ1(i, 0) = dZ1(i, 0) * Z1ReLUDerivative(i, 0);
	}

	Matrix XTransposed = XCol.Transpose();
	dW1 = dZ1 * XTransposed * (1 / Y.GetRows());
	Matrix dZ1Sum = Matrix(dZ2.GetRows(), 1, 0.0);
	for (i = 0; i < dZ1.GetRows(); i++)
	{
		for (j = 0; j < dZ1.GetCols(); j++)
		{
			dZ1Sum(i, 0) += dZ1(i, j);
		}
	}


	db1 = dZ1Sum * (1.0 / Y.GetRows());
}

void AI::UpdateParameters(float alpha)
{
	Matrix alphadW1 = (dW1 * alpha);
	Matrix alphadb1 = (db1 * alpha);
	Matrix alphadW2 = (dW2 * alpha);
	Matrix alphadb2 = (db2 * alpha);

	W1 = W1 - alphadW1;
	b1 = b1 - alphadb1;
	W2 = W2 - alphadW2;
	b2 = b2 - alphadb2;
}

int AI::GetPredictions(Matrix& A2)
{
	unsigned i, maxIndex = 0;
	double maxNum = 0.0;
	for (i = 0; i < A2.GetRows(); i++)
	{
		if (Y(i, 0) > maxNum)
		{
			maxNum = A2(i, 0);
			maxIndex = i;
		}
	}
	return maxIndex;
}

double AI::GetAccuracy()
{
	double accuracy = 0.0;
	for (unsigned i = 0; i < predictions.size(); i++) 
	{
		accuracy += predictions[i] == Y(i, 0);
	}

	return accuracy / (double)predictions.size();
}

void AI::GradientDescent(int iterations)
{
	//Initial Parameters
	W1 = Matrix(10, 784, 0.0);
	b1 = Matrix(10, 1, 0.0);
	W2 = Matrix(10, 10, 0.0);
	b2 = Matrix(10, 1, 0.0);
	InitializeWeightsAndBiases();


	unsigned i;
	for (i = 0; i < iterations; i++) 
	{
		GetCurrentX(i);
		ForwardPropagation();
		BackwardsPropagation();
		UpdateParameters(alpha);

		predictions.emplace_back(GetPredictions(A2));
		if (i % 100 == 0) 
		{
			DEBUG("Iteration: " + std::to_string(i));
			DEBUG(GetAccuracy());
		}
	}
}
