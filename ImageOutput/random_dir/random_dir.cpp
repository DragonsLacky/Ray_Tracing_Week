#include <iostream>
#include <corecrt_math_defines.h>
#include <fstream>
int main()
{
	std::ofstream file;
	file.open("coordinates.txt");
	int N = 1000000;
	float sum = 0.0;
	for (int i = 0; i < N; i++)
	{
		float r1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
		float r2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
		float x = cos(2 * M_PI * r1) * 2 * sqrt(r2 * (1 - r2));
		float y = sin(2 * M_PI * r1) * 2 * sqrt(r2 * (1 - r2));
		float z = 1 - r2;
		sum += z * z * z / (1.0 / (2.0 * M_PI));
		file << x << "\t" << y << "\t" << z << std::endl;
	}
	std::cout << "PI/2 = " << M_PI / 2 << std::endl;
	std::cout << "Estimate = " << sum / N << std::endl;
}