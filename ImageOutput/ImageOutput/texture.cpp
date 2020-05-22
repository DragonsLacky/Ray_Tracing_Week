#include "texture.h"


vec3 constant_texture::value(float u, float v, const vec3& p) const 
{
	return color;
}

vec3 checkered_texture::value(float u, float v, const vec3& p) const
{
	float sines = sin(10 * p.x()) * sin(10 * p.y()) * sin(10 * p.z());

	if (sines < 0)
	{
		return odd->value(u, v, p);
	}
	else 
	{
		return even->value(u, v, p);
	}
}

vec3 noise_texture::value(float u, float v, const vec3& p) const
{
	//return vec3(1.0f, 1.0f, 1.0f) * noise.noise(scale * p);
	//return vec3(1.0f, 1.0f, 1.0f) * noise.turbulence(scale * p);
	//return vec3(1.0f, 1.0f, 1.0f) * 0.5 *(1 + noise.turbulence(scale * p));
	return vec3(1.0f, 1.0f, 1.0f) * 0.5 * (1 + sin(scale * p.z() + 10 * noise.turbulence(p)));

}

vec3 image_texture::value(float u, float v, const vec3& p) const
{
	

	int i = u * nx;
	int j = (1 - v) * ny - 0.001;
	
	if (i < 0) i = 0;
	if (j < 0) j = 0;
	if (i >= nx - 1) i = nx - 1;
	if (j >= ny - 1) j = ny - 1;


	float r = static_cast<int>(data[3 * i + 3 * nx * j]) / 255.0f;
	float g = static_cast<int>(data[3 * i + 3 * nx * j + 1]) / 255.0f;
	float b = static_cast<int>(data[3 * i + 3 * nx * j + 2]) / 255.0f;

	return vec3(r, g, b);

}
