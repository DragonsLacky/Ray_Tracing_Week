#include <iostream>
#include <corecrt_math_defines.h>
#include <../ImageOutput/vec3.cpp>
#include <../ImageOutput/material.cpp>

inline float pdf(const vec3& p)
{
	return 1 / (4 * M_PI);
}

int main()
{
	int N = 1000000;
	float sum = 0;
	for (int i = 0; i < N; i++)
	{
		vec3 d = random_on_unit_sphere();
		//float random = static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 1);
		float cosine_sqr = d.z() * d.z();
		sum += cosine_sqr / pdf(d);
	}
	std::cout << "I = " << sum / N << std::endl;
}