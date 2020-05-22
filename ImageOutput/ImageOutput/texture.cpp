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