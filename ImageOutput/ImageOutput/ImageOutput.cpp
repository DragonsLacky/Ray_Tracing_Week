#include <iostream>
#include <fstream>

int main()
{
	int nx = 200;
	int ny = 100;

	std::ofstream fileoutput;
	fileoutput.open("image.ppm");

	fileoutput << "P3\n" << nx << " " << ny << "\n255\n";



	for (int i = ny - 1; i >= 0; i--)
	{
		for (int j = 0; j < nx; j++)
		{
			float r = float(j) / float(nx);
			float g = float(i) / float(ny);
			float b = 0.2;
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			fileoutput << ir << " " << ig << " " << ib << "\n";
		}
	}

	fileoutput.close();

	return 0;
}