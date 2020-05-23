#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int runs = 10000;
    int inside_circle = 0;
    int inside_circle_stratified = 0;
    for (int i = 0; i < runs; i++)
    {
        for (int j = 0; j < runs; j++)
        {
            float random1 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 1);
            float random2 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 1);
            float x = 2 * random1 - 1;
            float y = 2 * random2 - 1;
            if (x * x + y * y < 1)
            {
                inside_circle++;            
            }
            random1 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 1);
            random2 = static_cast<double>(rand()) / static_cast<double>(RAND_MAX + 1);
            x = 2 * ((i + random1) / runs) - 1;
            y = 2 * ((j + random1) / runs) - 1;
            if (x * x + y * y < 1)
            {
                inside_circle_stratified++;
            }
        }
    }

    std::cout << "Regular estimate of pi = " << 4 * static_cast<float>(inside_circle) / (runs*runs) << std::endl;
    std::cout << "Stratified Estimate of pi = " << 4 * static_cast<float>(inside_circle_stratified) / (runs*runs) << std::endl;


    return 0;
}
