#include "material.h"

vec3 random_in_unit_sphere()
{
	vec3 p;

	do {
		float random1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1.0);
		float random2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1.0);
		float random3 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1.0);

		p = 2.0f * vec3(random1, random2, random3) - vec3(1.0f, 1.0f, 1.0f);
	} while (p.squared_length() >= 1.0);
	return p;
}

vec3 random_on_unit_sphere()
{
	return unit_vector(random_in_unit_sphere());
}

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dot(v, n) * n;
}

float schlick(float cosine, float refraction_index) 
{
	float r0 = (1 - refraction_index) / (1 + refraction_index);
	r0 *= r0;

	return r0 + (1 - r0) * pow(1 - cosine, 5);
}

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted)
{
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0f - ni_over_nt * ni_over_nt *(1.0f - dt * dt);
	if (discriminant > 0)
	{
		refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
		return true;
	}
	else return false;
}

bool lambertian::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, float& pdf) const
{
	vec3 direction;
	do
	{
		direction = random_in_unit_sphere();
	} while (dot(direction, rec.normal) < 0);
	//vec3 target = rec.p + rec.normal + random_in_unit_sphere();
	scattered = ray(rec.p, unit_vector(direction /*target - rec.p*/), r_in.time());
	attenuation = albedo->value(rec.u, rec.v ,rec.p);
	pdf =  0.5 * M_PI; //dot(rec.normal, scattered.direction()) / M_PI;
	return true;
}


bool metal::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, float& pdf) const
{
	vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
	scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere(), r_in.time());
	attenuation = albedo;
	return (dot(scattered.direction(), rec.normal) > 0);
}

bool dielectric::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, float& pdf) const
{
	vec3 outward_normal;
	vec3 reflected = reflect(r_in.direction(), rec.normal);
	float ni_over_nt;
	attenuation = vec3(1.0f, 1.0f, 1.0f);
	vec3  refracted;
	float reflect_prob;
	float cosine;
	if (dot(r_in.direction(), rec.normal) > 0) 
	{
		outward_normal = -rec.normal;
		ni_over_nt = refraction_index;
		cosine = refraction_index * dot(r_in.direction(), rec.normal) / r_in.direction().length();
	}
	else {
		outward_normal = rec.normal;
		ni_over_nt = 1.0f / refraction_index;
		cosine = - dot(r_in.direction(), rec.normal) / r_in.direction().length();

	}
	if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) 
	{
		reflect_prob = schlick(cosine, refraction_index);
		//scattered = ray(rec.p, refracted);
	}
	else {
		scattered = ray(rec.p, reflected, r_in.time());
		reflect_prob = 1.0f;
	}
	float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
	if (random < reflect_prob) 
	{
		scattered = ray(rec.p, reflected, r_in.time());
	}
	else {
		scattered = ray(rec.p, refracted, r_in.time());
	}
	return true;
}

vec3 material::emitted(float u, float v, const vec3& p) const
{
	return vec3(0.0f, 0.0f, 0.0f);
}

bool diffuse_light::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, float &pdf) const
{
	return false;
}
vec3 diffuse_light::emitted(float u, float v, const vec3& p) const
{
	return emission->value(u, v, p);
}

bool isotropic::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered, float& pdf) const
{
	scattered = ray(rec.p, random_in_unit_sphere(), r_in.time());
	attenuation = albedo->value(rec.u, rec.v, rec.p);
	return false;
}

float material::scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const
{
	return false;
}

float lambertian::scattering_pdf(const ray& r_in, const hit_record& rec, const ray& scattered) const
{
	float cosine = dot(rec.normal, unit_vector(scattered.direction()));
	if (cosine < 0) cosine = 0;
	return cosine / M_PI;
}
