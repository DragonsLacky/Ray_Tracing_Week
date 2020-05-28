#include <iostream>
#include <corecrt_math_defines.h>
#include <fstream>
#include "../ImageOutput/vec3.cpp"

vec3 random_cosine_direction()
{
	float r1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
	float r2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
	float z = sqrt(1 - r2);
	float phi = 2 * M_PI * r1;
	float x = cos(phi) * 2 * sqrt(r2);
	float y = sin(phi) * 2 * sqrt(r2);
	return vec3(x, y, z);
}

int main()
{
	std::ofstream file;
	file.open("coordinates.txt");
	int N = 1000000;
	float sum = 0.0;
	for (int i = 0; i < N; i++)
	{
		vec3 v = random_cosine_direction();
		sum += v.z() * v.z() * v.z() / (v.z() /  M_PI);
		file << v.x() << "\t" << v.y() << "\t" << v.z() << std::endl;
	}
	std::cout << "PI/2 = " << M_PI / 2 << std::endl;
	std::cout << "Estimate = " << sum / N << std::endl;
}