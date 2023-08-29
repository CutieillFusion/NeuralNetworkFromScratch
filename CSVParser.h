#pragma once
#include "Image.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <string>

class CSVParser
{
public:
	CSVParser(const char* path);

	//Reads in and Parses File Data
	void ParseData(int images);
	//Creates Images
	void CreateImages(const char* relativePath);
	void CreateImageData();
	Matrix GetXData();
	Matrix GetYData();
private:
	std::string path;
	std::vector<std::string> fData;
	std::vector<std::vector<int>> data;
	Matrix X, Y;
};

