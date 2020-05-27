#include <iostream>

// X^2, from 0, to 2
int main()
{
	int inside_circle = 0;
	int inside_circle_stratified = 0;
	int N = 1000000;
	float sum = 0;
	for (int i = 0; i < N; i++)
	{
		float random = static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 1);
		float x = 2 * random;
		sum += x * x;
	}
	std::cout << "I = " << 2 * sum / N << std::endl;
}