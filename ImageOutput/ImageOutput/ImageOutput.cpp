#include <iostream>
#include <fstream>
#include <ctime>
#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "rectangle.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "box.h"
#include "transformations.h"
#include "volume.h"
#include "bvh.h"
#include "pdf.h"

float get_random_num()
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
}

vec3 color(const ray& r, hitable *world, int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, FLT_MAX, rec )) 
	{
		ray scattered;
		vec3 attenuation;
		vec3 emission = rec.mat_ptr->emitted(r, rec, rec.u, rec.v, rec.p);
		float pdf_val;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered, pdf_val))
		{
			hitable* light_shape = new xz_rectangle(213, 343, 227, 332, 554, 0);
			hittable_pdf p(light_shape, rec.p);
			scattered = ray(rec.p, p.generate(), r.time());
			pdf_val = p.value(scattered.direction());
			return emission + attenuation * rec.mat_ptr->scattering_pdf(r,rec,scattered) * color(scattered, world, depth + 1) / pdf_val;
		}
		else {
			return emission;
		}
	}
	else {
		/*vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * vec3(1.0f, 1.0f, 1.0f) + t * vec3(0.5f, 0.7f, 1.0f);*/
		return vec3(0.0f, 0.0f, 0.0f);
	}
}



hitable* create_scene()
{
	int n = 500;
	hitable **list = new  hitable*[n + 1];

	texture* checkered = new checkered_texture(new constant_texture(vec3(0.2f, 0.3f, 0.1f)), new constant_texture(vec3(0.9f, 0.9f, 0.9f)));
	list[0] = new sphere(vec3(0.0f, -1000.0f, 0.0f), 1000, new lambertian(checkered));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			
			vec3 center(a + 0.9 * get_random_num(), 0.2, b + 0.9 * get_random_num());

			if ((center - vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f) 
			{
				if (choose_mat < 0.8)
				{
					list[i++] = new moving_sphere(center, center + vec3(0.0f, 0.5f * get_random_num(), 0.0f), 0.0f, 1.0f,  0.2f, new lambertian(new constant_texture(vec3(get_random_num() * get_random_num(), get_random_num() * get_random_num(), get_random_num() * get_random_num()))));
				}
				else if (choose_mat < 0.95) 
				{
					list[i++] = new sphere(center, 0.2, new metal(vec3(0.5 * (1 +get_random_num()), 0.5 * (1 + get_random_num()), 0.5 * (1 + get_random_num())),0.5 * get_random_num()));

				}
				else {
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new sphere(vec3(0.0f, 1.0f, 0.0f), 1.0f, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4.0f, 1.0f, 0.0f), 1.0f, new lambertian(new constant_texture(vec3(0.4f, 0.2f, 0.1f))));
	list[i++] = new sphere(vec3(4.0f, 1.0f, 0.0f), 1.0f, new metal(vec3(0.7f, 0.6f, 0.5f), 0.0f));

	return new hitable_list(list, i);
}

hitable* two_spheres()
{
	texture* checkered = new checkered_texture(new constant_texture(vec3(0.2f, 0.3f, 0.1f)), new constant_texture(vec3(0.9f, 0.9f, 0.9f)));
	int n = 50;
	hitable** list = new hitable * [n + 1];
	list[0] = new sphere(vec3(0.0f, -10.0f, 0.0f), 10.0f, new lambertian(checkered));
	list[1] = new sphere(vec3(0.0f, 10.0f, 0.0f), 10.0f, new lambertian(checkered));
	
	return new hitable_list(list, 2);
}

hitable* two_perlin_spheres()
{
	texture* pertext = new noise_texture(4);
	hitable** list = new hitable*[2];

	list[0] = new sphere(vec3(0.0f, -1000.0f, 0.0f), 1000.0f, new lambertian(pertext));
	list[1] = new sphere(vec3(0.0f, 2.0f, 0.0f), 2.0f, new lambertian(pertext));
	return new hitable_list(list, 2);
}

hitable* earth_image()
{
	int nx, ny, nn;
	unsigned char* tex_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);
	if (!tex_data) {
		std::cout << "texture not loaded" << std::endl;
	}
	material* mat = new lambertian(new image_texture(tex_data, nx, ny));
	hitable** list = new hitable * [1];

	//list[0] = new sphere(vec3(0.0f, -1000.0f, 0.0f), 1000.0f, new lambertian(pertext));
	list[0] = new sphere(vec3(0.0f, 0.0f, 0.0f), 2.0f, mat);
	return new hitable_list(list, 1);
}

hitable* simple_light()
{
	texture* pertext = new noise_texture(4);
	hitable** list = new hitable * [4];

	list[0] = new sphere(vec3(0.0f, -1000.0f, 0.0f), 1000.0f, new lambertian(pertext));
	list[1] = new sphere(vec3(0.0f, 2.0f, 0.0f), 2.0f, new lambertian(pertext));
	list[2] = new sphere(vec3(0.0f, 7.0f, 0.0f), 2.0f, new diffuse_light(new constant_texture(vec3(4.0f, 4.0f, 4.0f))));
	list[3] = new xy_rectangle(3.0f, 5.0f, 1.0f, 3.0f, -2.0f, new diffuse_light(new constant_texture(vec3(4.0f, 4.0f, 4.0f))));
	return new hitable_list(list, 4);
}

hitable* cornell_box(camera** cam, float aspect)
{
	hitable** list = new hitable * [50];
	int i = 0;

	material* red = new lambertian(new constant_texture(vec3(0.65f, 0.05f, 0.05f)));
	material* white = new lambertian(new constant_texture(vec3(0.73f, 0.73f, 0.73f)));
	material* green = new lambertian(new constant_texture(vec3(0.12f, 0.45f, 0.15f)));
	material* light = new diffuse_light(new constant_texture(vec3(15.0f, 15.0f, 15.0f)));

	list[i++] = new flip_normals( new yz_rectangle(0, 555, 0, 555, 555, green));
	list[i++] = new yz_rectangle(0, 555, 0, 555, 0, red);
	list[i++] = new flip_normals(new xz_rectangle(213, 343, 227, 332, 554, light));
	list[i++] = new flip_normals(new xz_rectangle(0, 555, 0, 555, 555, white));
	list[i++] = new xz_rectangle(0, 555, 0, 555, 0, white);
	list[i++] = new flip_normals(new xy_rectangle(0, 555, 0, 555, 555, white));

	//list[i++] = new box(vec3(130, 0, 65), vec3(295, 165, 230), white);
	//list[i++] = new box(vec3(265, 0, 295), vec3(430, 330, 460), white);
	
	vec3 look_from(278.0f, 278.0f, -800.0f);
	vec3 look_at(278.0f, 278.0f, 0.0f);
	float dist_to_focus = 10.0f;
	float aperture = 0.0f;
	float vfov = 40.0f;

	*cam = new camera(look_from, look_at, vec3(0.0f, 1.0f, 0.0f), vfov, aspect, aperture, dist_to_focus, 0.0f, 1.0f);


	list[i++] = new translate(new rotate_y(new box(vec3(0.0, 0.0, 0.0), vec3(165, 165, 165), white), -18), vec3(130, 0, 65));
	list[i++] = new translate(new rotate_y(new box(vec3(0.0, 0.0, 0.0), vec3(165, 330, 165), white), 15), vec3(265, 0, 295));

	return new hitable_list(list, i);
}

hitable* conrnell_volume()
{
	hitable** list = new hitable * [50];
	int i = 0;

	material* red = new lambertian(new constant_texture(vec3(0.65f, 0.05f, 0.05f)));
	material* white = new lambertian(new constant_texture(vec3(0.73f, 0.73f, 0.73f)));
	material* green = new lambertian(new constant_texture(vec3(0.12f, 0.45f, 0.15f)));
	material* light = new diffuse_light(new constant_texture(vec3(7.0f, 7.0f, 7.0f)));

	list[i++] = new flip_normals(new yz_rectangle(0, 555, 0, 555, 555, green));
	list[i++] = new yz_rectangle(0, 555, 0, 555, 0, red);
	list[i++] = new xz_rectangle(113, 443, 127, 432, 554, light);
	list[i++] = new flip_normals(new xz_rectangle(0, 555, 0, 555, 555, white));
	list[i++] = new xz_rectangle(0, 555, 0, 555, 0, white);
	list[i++] = new flip_normals(new xy_rectangle(0, 555, 0, 555, 555, white));

	//list[i++] = new box(vec3(130, 0, 65), vec3(295, 165, 230), white);
	//list[i++] = new box(vec3(265, 0, 295), vec3(430, 330, 460), white);

	list[i++] = new constant_volume( new translate(new rotate_y(new box(vec3(0.0, 0.0, 0.0), vec3(165, 165, 165), white), -18), vec3(130, 0, 65)), 0.01, new constant_texture(vec3(1.0f, 1.0f, 1.0f)));
	list[i++] = new constant_volume(new translate(new rotate_y(new box(vec3(0.0, 0.0, 0.0), vec3(165, 330, 165), white), 15), vec3(265, 0, 295)), 0.01, new constant_texture(vec3(0.0f, 0.0f, 0.0f)));

	return new hitable_list(list, i);
}

hitable* Full_scene()
{
	int nb = 20;
	int b = 0, l = 0;;
	hitable** list = new hitable * [30];
	hitable** boxlist1 = new hitable * [10000];
	hitable** boxlist2 = new hitable * [10000];
	material* white = new lambertian(new constant_texture(vec3(0.73f, 0.73f, 0.73f)));
	material* ground = new lambertian(new constant_texture(vec3(0.48, 0.83, 0.53)));
	material* light = new diffuse_light(new constant_texture(vec3(7, 7, 7)));
	for (int i = 0; i < nb; i++)
	{
		for (int j = 0; j < nb; j++)
		{
			float w = 100;
			float x0 = -1000 + i * w;
			float z0 = -1000 + j * w;
			float y0 = 0;
			float x1 = x0 + w;
			float y1 = 100 * (get_random_num() + 0.01f);
			float z1 = z0 + w;
			boxlist1[b++] = new box(vec3(x0, y0, z0), vec3(x1, y1, z1), ground);
		}
	}
	vec3 center(400, 400, 200);
	list[l++] = new bvh_node(boxlist1, b, 0, 1);
	list[l++] = new xz_rectangle(123, 423, 147, 412, 554, light);
	list[l++] = new moving_sphere(center, center + vec3(30, 0, 0), 0, 1, 50, new lambertian(new constant_texture(vec3(0.7, 0.7, 0.1))));
	list[l++] = new sphere(vec3(260, 150, 45), 50, new dielectric(1.5));
	list[l++] = new sphere(vec3(0, 150, 145), 50, new metal(vec3(0.8, 0.8, 0.8), 10.0));
	hitable* bounds = new sphere(vec3(360, 150, 145), 70, new dielectric(1.5));
	list[l++] = bounds;

	list[l++] = new constant_volume(bounds, 0.2, new constant_texture(vec3(0.2, 0.4, 0.9)));
	list[l++] = new constant_volume(new sphere(vec3(0.0, 0.0, 0.0), 5000, new dielectric(1.5)), 0.001, new constant_texture(vec3(1.0, 1.0, 1.0)));
	int nx, ny, nn;
	unsigned char* tex_data = stbi_load("earthmap.jpg", &nx, &ny, &nn, 0);
	material* mat = new lambertian(new image_texture(tex_data, nx, ny));
	list[l++] = new sphere(vec3(400, 280, 400), 100, mat);
	texture* pertex = new noise_texture(0.1);
	list[l++] = new sphere(vec3(220, 280, 300), 80, new lambertian(pertex));
	int ns = 1000;
	for (int i = 0; i < ns; i++)
	{
		boxlist2[i] = new sphere(vec3(165 * get_random_num(), 165 * get_random_num(), 165 * get_random_num()), 10, white);
	}
	list[l++] = new translate(new rotate_y(new bvh_node(boxlist2, ns, 0.0, 1.0), 15), vec3(-100, 270, 395));
	return new hitable_list(list, l);
}

int main()
{
	int nx = 500;
	int ny = 500;
	int ns = 10;

	std::ofstream fileoutput;
	fileoutput.open("image.ppm");

	float R = cos(M_PI / 4);

	fileoutput << "P3\n" << nx << " " << ny << "\n255\n";

	//hitable* list[5];
	//list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
	//list[1] = new sphere(vec3( R, 0, -1), R, new lambertian(vec3(1, 0, 0)));

	/*list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1.0f, 0.0f, -1.0f), 0.5, new metal(vec3(0.8, 0.6, 0.2),0.3));
	list[3] = new sphere(vec3(-1.0, 0.0f, -1.0f), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1.0, 0.0f, -1.0f), -0.45, new dielectric(1.5));*/
	
	camera** cam = new camera*[0];

	hitable* world = cornell_box(cam, nx / ny);

	vec3 look_from(278.0f, 278.0f, -800.0f);
	vec3 look_at(278.0f, 278.0f, 0.0f);
	float dist_to_focus = 10.0f;
	float aperture = 0.0f;
	float vfov = 40.0f;
	float aspect = nx / ny;
	/*vec3 look_from(478.0f, 278.0f, -600.0f);
	vec3 look_at(278.0f, 278.0f, 0.0f);
	float dist_to_focus = 10.0f;
	float aperture = 0.0f;*/

	//camera cam(look_from, look_at, vec3(0.0f, 1.0f, 0.0f), 40, nx / ny, aperture, dist_to_focus, 0.0f, 1.0f); 
		;
	int count = 0;

	for (int i = ny - 1; i >= 0; i--)
	{
		for (int j = 0; j < nx; j++)
		{
			vec3 col(0.0f, 0.0f, 0.0f);
			for (int s = 0; s < ns; s++)
			{
			float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
			float u = static_cast<float>(j + random) / static_cast<float>(nx);
			float v = static_cast<float>(i + random) / static_cast<float>(ny);
			ray r = (*cam)->get_ray(u, v);
			vec3 p = r.point(2.0);
			col += color(r, world, 0);

			}
			
			col /= static_cast<float>(ns);

			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

			int ir = int(255.99 * col.r());
			int ig = int(255.99 * col.g());
			int ib = int(255.99 * col.b());
			fileoutput << ir << " " << ig << " " << ib << "\n";
			std::cout << count++ << std::endl;
		}
	}

	fileoutput.close();

	return 0;
}