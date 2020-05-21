#include <iostream>
#include <fstream>
#include <ctime>
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"


vec3 color(const ray& r, hitable *world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec )) 
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else {
			return vec3(0.0f, 0.0f, 0.0f);
		}
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
	}
}

int main()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;

	std::ofstream fileoutput;
	fileoutput.open("image.ppm");

	float R = cos(M_PI / 4);

	fileoutput << "P3\n" << nx << " " << ny << "\n255\n";

	hitable* list[5];
	//list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
	//list[1] = new sphere(vec3( R, 0, -1), R, new lambertian(vec3(1, 0, 0)));

	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1.0f, 0.0f, -1.0f), 0.5, new metal(vec3(0.8, 0.6, 0.2),0.3));
	list[3] = new sphere(vec3(-1.0, 0.0f, -1.0f), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1.0, 0.0f, -1.0f), -0.45, new dielectric(1.5));

	hitable* world = new hitable_list(list, 5);
	camera cam(vec3(-2, 2, 1), vec3(0, 0, -1), vec3(0, 1, 0), 20, nx / ny);

	std::srand(static_cast<float>(std::time(nullptr)));

	for (int i = ny - 1; i >= 0; i--)
	{
		for (int j = 0; j < nx; j++)
		{
			vec3 col(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < ns; s++)
			{
			float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			float u = static_cast<float>(j + random) / static_cast<float>(nx);
			float v = static_cast<float>(i + random) / static_cast<float>(ny);
			ray r = cam.get_ray(u, v);
			vec3 p = r.point(2.0);
			col += color(r, world, 0);

			}
			
			col /= static_cast<float>(ns);

			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99 * col.r());
			int ig = int(255.99 * col.g());
			int ib = int(255.99 * col.b());
			fileoutput << ir << " " << ig << " " << ib << "\n";
		}
	}

	fileoutput.close();

	return 0;
}