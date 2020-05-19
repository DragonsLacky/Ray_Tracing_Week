#include <iostream>
#include <fstream>
#include "vec3.h"

int main()
{
	int nx = 200;
	int ny = 100;

	std::ofstream fileoutput;
	fileoutput.open("image.ppm");

	fileoutput << "P3\n" << nx << " " << ny << "\n255\n";



	for (int i = ny - 1; i >= 0; i--)
	{
		for (int j = 0; j < nx; j++)
		{
			vec3 colour(static_cast<float>(j) / static_cast<float>(nx), static_cast<float>(i) / static_cast<float>(ny), 0.2);
			int ir = int(255.99 * colour.r());
			int ig = int(255.99 * colour.g());
			int ib = int(255.99 * colour.b());
			fileoutput << ir << " " << ig << " " << ib << "\n";
		}
	}

	fileoutput.close();

	return 0;
}