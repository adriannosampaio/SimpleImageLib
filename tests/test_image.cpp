#include <iostream>
#include "image.hpp"

#include <typeinfo>

int main()
{
	using namespace SimpleImageLib;

	int width = 4, 
		height = 4, 
		components = 1;

	Image img(width, height, components);

	for(int r = 0; r < height; r++)
	{
		for(int c = 0; c < width; c++)
		{
			for(int cp = 0; cp < components; cp++)
			{
				auto&& comp = img[r][c][cp];
				comp += r * width + c;
				std::cout << comp << " ("<< typeid(comp).name() <<") ";
			}
		}
		std::cout << "\n";
	}

	return 0;

}