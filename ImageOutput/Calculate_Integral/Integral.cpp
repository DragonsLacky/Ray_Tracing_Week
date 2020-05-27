#include <iostream>

// X^2, from 0, to 2

inline float pdf(float x)
{
	return 0.5 * x;
}

int main()
{
	int inside_circle = 0;
	int inside_circle_stratified = 0;
	int N = 10000;
	float sum = 0;
	for (int i = 0; i < N; i++)
	{
		float random = static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 1);
		float x = sqrt(4 * random);
		sum += (x * x / pdf(x));
	}
	std::cout << "I = " << sum / N << std::endl;
}