#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int N = 1000;
    int inside_circle = 0;
    for (int i = 0; i < N; i++)
    {
        float random1 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 1);
        float random2 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 1);
        
        std::cout << random1 << " " << random2 << "\n";

        float x = 2 * random1 - 1;
        float y = 2 * random2 - 1;
        if (x * x + y * y < 1)
            inside_circle++;            
    }
    std::cout << "Estimate of pi = " << 4 * static_cast<float>(inside_circle) / N << std::endl;
    return 0;
}
