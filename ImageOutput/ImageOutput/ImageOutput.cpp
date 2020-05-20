#include <iostream>
#include <fstream>
#include <ctime>
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"

vec3 random_in_unit_sphere()
{
	vec3 p;

	do {
		float random1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
		float random2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		float random3 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

		p = 2.0f * vec3(random1, random1, random1) - vec3(1.0f, 1.0f, 1.0f);
	} 
	while (p.squared_length() >= 1.0);
	return p;
}

vec3 color(const ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec )) 
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5f * color( ray(rec.p, target - rec.p), world);
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

	fileoutput << "P3\n" << nx << " " << ny << "\n255\n";

	hitable* list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);

	hitable* world = new hitable_list(list, 2);
	camera cam;

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

			col += color(r, world);

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