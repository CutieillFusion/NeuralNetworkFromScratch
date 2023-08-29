#include "Image.h"

#include <iostream>
#include <fstream>

Color::Color() : r(0), g(0), b(0)
{
}

Color::Color(int r, int g, int b) : r(r), b(b), g(g)
{
}

Color::~Color()
{
}

Image::Image(int width, int height) : m_width(width), m_height(height), m_colors(std::vector<Color>(width * height))
{
}

Image::~Image()
{
}

Color Image::GetColor(int x, int y) const
{
	return m_colors[y * m_width + x];
}

void Image::SetColor(const Color& color, int x, int y)
{
	//Sets Individual Values like a Copy Constructor
	m_colors[y * m_width + x].r = color.r;
	m_colors[y * m_width + x].b = color.b;
	m_colors[y * m_width + x].g = color.g;
}

void Image::Export(const char* path)
{
	std::ofstream f;
	
	//Opens File
	f.open(path, std::ios::out | std::ios::binary);

	//Checks if Actually Open
	if (!f.is_open()) 
	{
		std::cout << "File could not be opened" << std::endl;
		return;
	}

	//3 Byte Bitmap Padding
	unsigned char bmpPad[3] = { 0, 0, 0 };
	//Calculates Padding | (Byte Space - (Color Space * Number of Color Channels) % Byte Space) % Byte Space (Extra Check)
	const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);
	
	//Always 14 Bytes
	const int fileHeaderSize = 14;
	//Always 40 Bytes
	const int informationHeaderSize = 40;		
	//Total File Size
	const int fileSize = fileHeaderSize + informationHeaderSize + m_width * m_height * 3 + paddingAmount * m_height;

	//File Header (Holds Header Data)
	unsigned char fileHeader[fileHeaderSize];

	//File Type
	fileHeader[0] = 'B';
	fileHeader[1] = 'M';
	//File Size
	fileHeader[2] = fileSize;
	fileHeader[3] = fileSize >> 8;
	fileHeader[4] = fileSize >> 16;
	fileHeader[5] = fileSize >> 24;
	//Reserved 1 (Not Used)
	fileHeader[6] = 0;
	fileHeader[7] = 0;
	//Reserved 2 (Not Used)
	fileHeader[8] = 0;
	fileHeader[9] = 0;
	//Pixel Data Offset
	fileHeader[10] = fileHeaderSize + informationHeaderSize;
	fileHeader[11] = 0;
	fileHeader[12] = 0;
	fileHeader[13] = 0;

	//Information Header (Holds Image Specs)
	unsigned char informationHeader[informationHeaderSize];

	//Header Size
	informationHeader[0] = informationHeaderSize;
	informationHeader[1] = 0;
	informationHeader[2] = 0;
	informationHeader[3] = 0;
	//Image Width
	informationHeader[4] = m_width;
	informationHeader[5] = m_width >> 8;
	informationHeader[6] = m_width >> 16;
	informationHeader[7] = m_width >> 24;
	//Image Height 
	informationHeader[8] = m_height;
	informationHeader[9] = m_height >> 8;
	informationHeader[10] = m_height >> 16;
	informationHeader[11] = m_height >> 24;
	//Planes
	informationHeader[12] = 1;
	informationHeader[13] = 0;
	//Bits per Pixel (RGB)
	informationHeader[14] = 24;
	informationHeader[15] = 0;
	//Compression (No Compression)
	informationHeader[16] = 0;
	informationHeader[17] = 0;
	informationHeader[18] = 0;
	informationHeader[19] = 0;
	//Image Size (No Compression)
	informationHeader[20] = 0;
	informationHeader[21] = 0;
	informationHeader[22] = 0;
	informationHeader[23] = 0;
	// X Pixels per Meter (Not Specified)
	informationHeader[24] = 0;
	informationHeader[25] = 0;
	informationHeader[26] = 0;
	informationHeader[27] = 0;
	// Y Pixels per Meter (Not Specified)
	informationHeader[28] = 0;
	informationHeader[29] = 0;
	informationHeader[30] = 0;
	informationHeader[31] = 0;
	// Total Colors (Color Palette not used)
	informationHeader[32] = 0;
	informationHeader[33] = 0;
	informationHeader[34] = 0;
	informationHeader[35] = 0;
	// Important Colors (Generally Ignored)
	informationHeader[36] = 0;
	informationHeader[37] = 0;
	informationHeader[38] = 0;
	informationHeader[39] = 0;

	//Sets File Header and Information Header Data
	f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
	f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

	//Sets Pixel Data
	for (int y = 0; y < m_height; y++) 
	{
		for (int x = 0; x < m_width; x++) 
		{
			//Casts Floats to Bytes
			unsigned char r = static_cast<unsigned char>(GetColor(x, y).r);
			unsigned char g = static_cast<unsigned char>(GetColor(x, y).g);
			unsigned char b = static_cast<unsigned char>(GetColor(x, y).b);

			//Flipped I don't know why tho
			unsigned char color[] = { b, g, r };

			//Writes Color Data
			f.write(reinterpret_cast<char*>(color), 3);
		}
		//Writes Padding Data
		f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
	}

	//Closes File
	f.close();
}
