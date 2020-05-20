#include <iostream>
#include <fstream>
#include "hitable_list.h"
#include "sphere.h"

vec3 color(const ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.0, FLT_MAX, rec )) 
	{
		return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
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

	std::ofstream fileoutput;
	fileoutput.open("image.ppm");

	fileoutput << "P3\n" << nx << " " << ny << "\n255\n";

	vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
	vec3 horizontal(4.0f, 0.0f, 0.0f);
	vec3 vertical(0.0f, 2.0f, 0.0f);
	vec3 origin(0.0f, 0.0f, 0.0f);

	hitable* list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);

	hitable* world = new hitable_list(list, 2);

	for (int i = ny - 1; i >= 0; i--)
	{
		for (int j = 0; j < nx; j++)
		{
			float u = static_cast<float>(j) / static_cast<float>(nx);
			float v = static_cast<float>(i) / static_cast<float>(ny);

			ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			vec3 col(color(r, world));

			int ir = int(255.99 * col.r());
			int ig = int(255.99 * col.g());
			int ib = int(255.99 * col.b());
			fileoutput << ir << " " << ig << " " << ib << "\n";
		}
	}

	fileoutput.close();

	return 0;
}