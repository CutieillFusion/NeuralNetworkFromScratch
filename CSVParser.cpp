#include "CSVParser.h"

#define DEBUG(x) std::cout << x << std::endl

CSVParser::CSVParser(const char* path) : path(path)
{
	
}

void CSVParser::ParseData(int images)
{
	std::fstream f;
	//Opens File
	f.open(path, std::ios::in);

	//Checks if Actually Open
	if (!f.is_open())
	{
		std::cout << "Error openning File" << std::endl;
		return;
	}

	//Loops through File Line by Line
	int fDataIndex = 0;
	for (int i = 0; i < images; i++)
	{
		if (i % 10000 == 0)
		{
			DEBUG(i);
		}
		fData.emplace_back("");
		std::getline(f, fData[fDataIndex]);
		fData[fDataIndex++] += '\n';
	}

	//Closes File
	f.close();

	//Converts from String to Int
	std::string temp;
	for (int i = 0; i < fData.size(); i++)
	{
		if (i % 10000 == 0)
		{
			DEBUG(i);
		}
		//Increases Size by 1
		data.resize(data.size() + 1, {});
		for (int j = 0; j < fData[i].length(); j++)
		{
			//Adds Data when at a Comma
			if (fData[i][j] == ',')
			{
				//Places in the Back of the Vector
				data[i].emplace_back(std::stoi(temp));
				//Creates a Empty String
				temp.clear();
				continue;
			}
			//Stores new Char
			temp += fData[i][j];
		}
		//Places last number in the back of the Vector
		data[i].emplace_back(std::stoi(temp));
		//Creates a Empty String
		temp.clear();
	}
}

void CSVParser::CreateImages(const char* relativePath)
{
	//Hard Coded Dimensions
	const int width = 28;
	const int height = 28;

	//Loops Through Data 
	for (int i = 0; i < data.size(); i++)
	{
		//Creates Image
		Image image(width, height);

		//Loops through Pixel Data
		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				//Sets Color to Position
				image.SetColor(Color(data[i][x + y * width + 1], data[i][x + y * width + 1], data[i][x + y * width + 1]), x, y);
			}
		}

		//Creates Name and Path for Image
		std::string name = "#" + std::to_string(i + 1) + " (" + std::to_string(data[i][0]) + ").bmp";
		image.Export((relativePath + name).c_str());
	}
}

void CSVParser::CreateImageData()
{
	X = Matrix(784, data.size(), 0.0);
	Y = Matrix(data.size(), 1, 0.0);
	unsigned i, j;
	for (i = 0; i < data.size(); i++) 
	{
		if (i % 10000 == 0)
		{
			DEBUG(i);
		}
		Y(i,0) = data[i][0];
		for (j = 1; j < data[i].size(); j++) 
		{
			X(j - 1, i) = data[i][j];
		}
	}
}

Matrix CSVParser::GetXData()
{
	return X;
}

Matrix CSVParser::GetYData()
{
	return Y;
}
