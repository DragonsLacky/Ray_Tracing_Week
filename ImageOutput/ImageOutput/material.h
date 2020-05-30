#pragma once
#include "ray.h"
#include "hitable.h"
#include "texture.h"
#include "onb.h"
#include "pdf.h"

struct scatter_record
{
	ray specular_ray;
	bool is_specular;
	vec3 attenuation;
	pdf* pdf_ptr;
};

class material
{
public:
	virtual bool scatter(const ray& r_in, const hit_record& h_rec, scatter_record& s_rec) const = 0;
	virtual vec3 emitted(const ray& r_in, const hit_record& rec, float u, float v, const vec3& p) const;
	virtual float scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const;
};

class lambertian :
	public material
{
public:
	lambertian(texture* a) : albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& h_rec, scatter_record& s_rec) const;
	virtual float scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const;
	texture* albedo;
};

class metal : public material
{
public:
	metal(const vec3& a, float f) : albedo(a), fuzz(f) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, scatter_record& s_rec) const;
	vec3 albedo;
	float fuzz;
};

class dielectric : public material
{
public:
	dielectric(float ri) : refraction_index(ri) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, scatter_record& s_rec) const;
	
	float refraction_index;
};

class diffuse_light : public material
{
public:
	diffuse_light(texture* a) : emission(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, scatter_record& s_rec) const;
	virtual vec3 emitted(const ray& r_in, const hit_record& rec, float u, float v, const vec3& p) const;

	texture* emission;
};

class isotropic : public material
{
public:
	isotropic(texture* t) : albedo(t) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, scatter_record& s_rec) const;
	texture* albedo;
};

vec3 random_in_unit_sphere();
vec3 random_on_unit_sphere();
vec3 reflect(const vec3& v, const vec3& n);
bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted);
float schlick(float cosine, float refraction_index);