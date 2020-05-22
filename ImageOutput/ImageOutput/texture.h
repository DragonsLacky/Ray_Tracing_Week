#pragma once
#include "ray.h"
#include "perlin.h"

class texture
{
public:
	virtual vec3 value(float u, float v, const vec3& p) const = 0;

	vec3 color;
};

class constant_texture : public texture
{
public:
	constant_texture() = default;
	constant_texture(vec3 c) : color(c) {}
	virtual vec3 value(float u, float v, const vec3& p) const;
	vec3 color;
};

class checkered_texture : public texture
{
public:
	checkered_texture() = default;
	checkered_texture(texture* t1, texture* t2) : odd(t1), even(t2) {}
	virtual vec3 value(float u, float v, const vec3& p) const;
	texture* odd;
	texture* even;
};

class noise_texture : public texture
{
public:
	noise_texture() = default;
	noise_texture(float sc) : scale(sc) {}
	virtual vec3 value(float u, float v, const vec3& p) const;
	perlin noise;
	float scale;
};