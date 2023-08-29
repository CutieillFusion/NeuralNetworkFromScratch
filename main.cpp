#include "Matrix.h"
#include "CSVParser.h"
#include "Image.h"
#include "AI.h"

#include <iostream>
#include <cstdlib>	
#include <math.h>

#define DEBUG(x) std::cout << x << std::endl

int main() 
{	
	CSVParser parser ("image.csv");
	parser.ParseData(1000);
	parser.CreateImageData();

	Matrix X = parser.GetXData();
	Matrix Y = parser.GetYData();

	AI ai(X, Y);
	ai.GradientDescent(5);

	return 0;
}

//Notes:
//Dev Data - Hold Some data to stop overfitting