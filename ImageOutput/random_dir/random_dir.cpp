#include <iostream>
#include <corecrt_math_defines.h>
#include <fstream>
int main()
{
	std::ofstream file;
	file.open("coordinates.txt");
	for (int i = 0; i < 200; i++)
	{
		float r1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
		float r2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
		float x = cos(2 * M_PI * r1) * 2 * sqrt(r2 * (1 - r2));
		float y = sin(2 * M_PI * r1) * 2 * sqrt(r2 * (1 - r2));
		float z = 1 - 2 * r2;
		file << x << "\t" << y << "\t" << z << std::endl;
	}
}