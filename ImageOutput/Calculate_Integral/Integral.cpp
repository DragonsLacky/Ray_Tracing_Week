#include <iostream>

// X^2, from 0, to 2

inline float pdf(float x)
{
	return 3 * x * x / 8;
}

int main()
{
	int inside_circle = 0;
	int inside_circle_stratified = 0;
	int N = 1;
	float sum = 0;
	for (int i = 0; i < N; i++)
	{
		float random = static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 1);
		float x = pow(8 * random, 1.0f/3.0f);
		sum += (x * x / pdf(x));
	}
	std::cout << "I = " << sum / N << std::endl;
}