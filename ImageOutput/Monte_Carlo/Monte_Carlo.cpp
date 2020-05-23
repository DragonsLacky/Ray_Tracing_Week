#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int runs = 0;
    int inside_circle = 0;
    while (true)
    {
        runs++;
        float random1 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 1);
        float random2 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 1);
        
        float x = 2 * random1 - 1;
        float y = 2 * random2 - 1;
        if (x * x + y * y < 1)
        {
            inside_circle++;            
        }
        if (runs % 100000 == 0)
        {
            std::cout << "Estimate of pi = " << 4 * static_cast<float>(inside_circle) / runs++ << std::endl;
        }
    }
    return 0;
}
