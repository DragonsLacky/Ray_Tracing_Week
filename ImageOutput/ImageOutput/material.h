#pragma once
#include "ray.h"
#include "hitable.h"
#include "texture.h"
#include <corecrt_math_defines.h>

class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered,float& pdf) const = 0;
	virtual vec3 emitted(float u, float v, const vec3& p) const;
	virtual float scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const;
};

class lambertian :
	public material
{
public:
	lambertian(texture* a) : albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, float& pdf) const;
	virtual float scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const;
	texture* albedo;
};

class metal : public material
{
public:
	metal(const vec3& a, float f) : albedo(a), fuzz(f) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, float& pdf) const;
	vec3 albedo;
	float fuzz;
};

class dielectric : public material
{
public:
	dielectric(float ri) : refraction_index(ri) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, float& pdf) const;
	
	float refraction_index;
};

class diffuse_light : public material
{
public:
	diffuse_light(texture* a) : emission(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, float& pdf) const;
	virtual vec3 emitted(float u, float v, const vec3& p) const;

	texture* emission;
};

class isotropic : public material
{
public:
	isotropic(texture* t) : albedo(t) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, float& pdf) const;
	texture* albedo;
};

vec3 random_in_unit_sphere();
vec3 random_on_unit_sphere();
vec3 reflect(const vec3& v, const vec3& n);
bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted);
float schlick(float cosine, float refraction_index);