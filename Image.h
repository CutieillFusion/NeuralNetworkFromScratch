#pragma once
#include <vector>

//Possibly Recode into 1 byte struct for Brightness since its a gray scale image
struct Color
{
	//Color Range of 0 - 255
	int r, g, b;

	Color();
	Color(int r, int g, int b);
	~Color();
};

class Image
{
public:
	Image(int width, int height);
	~Image();

	Color GetColor(int x, int y) const;
	void SetColor(const Color& color, int x, int y);

	//Creates Image
	void Export(const char* path);
private:
	int m_width;
	int m_height;
	std::vector<Color> m_colors;
};

