#pragma once
#include "sphere.h"
#include <math.h>

void get_sphere_uv(const vec3& p, float& u, float& v)
{
	float phi = atan2(p.z(), p.x());
	float theta = asin(p.y());

	u = 1 - (phi + M_PI) / (2 * M_PI);
	v = (theta + M_PI / 2) / M_PI;
}

vec3 random_to_sphere(float radius, float distance_sqr)
{
	float r1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
	float r2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
	float z = 1 + r2 * (sqrt(1 - radius * radius / distance_sqr) - 1);
	float phi = 2 * M_PI * r1;
	float x = cos(phi) * sqrt(1 - z * z);
	float y = sin(phi) * sqrt(1 - z * z);
	return vec3(x, y, z);
}


bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - center;

	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc,oc) - radius * radius;

	float discriminant = b * b - a * c;

	if (discriminant > 0) 
	{
		float temp = (-b - sqrt(discriminant)) / a;

		if (temp < t_max && temp > t_min) 
		{
			rec.t = temp;
			rec.p = r.point(rec.t);
			vec3 outward_normal = (rec.p - center) / radius;
			set_face(r, outward_normal, rec);
			get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
			rec.mat_ptr = mat_ptr;
			return true;
		}
		
		temp = (-b + sqrt(discriminant)) / a;

		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.point(rec.t);
			vec3 outward_normal = (rec.p - center) / radius;
			set_face(r, outward_normal, rec);
			get_sphere_uv((rec.p - center) / radius, rec.u, rec.v);
			rec.mat_ptr = mat_ptr;
			return true;
		}

	}
	return false;
}

vec3 moving_sphere::center(float time) const 
{
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool moving_sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - center(r.time());

	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;

	float discriminant = b * b - a * c;

	if (discriminant > 0)
	{
		float temp = (-b - sqrt(discriminant)) / a;

		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.point(rec.t);
			rec.normal = (rec.p - center(r.time())) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}

		temp = (-b + sqrt(discriminant)) / a;

		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.point(rec.t);
			rec.normal = (rec.p - center(r.time())) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}

	}
	return false;
}
bool sphere::bounding_box(float t0, float t1, boundary& box) const
{
	box = boundary(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
	return true;
}

bool moving_sphere::bounding_box(float t0, float t1, boundary& box) const
{
	boundary box0 = boundary(center(t0) - vec3(radius, radius, radius), center(t0) + vec3(radius, radius, radius));
	boundary box1 = boundary(center(t1) - vec3(radius, radius, radius), center(t1) + vec3(radius, radius, radius));

	box = surrounding_box(box0, box1);
	return true;
}


float sphere::pdf_value(const vec3& o, const vec3& v) const
{
	hit_record rec;
	if (this->hit(ray(o, v), 0.001, FLT_MAX, rec))
	{
		float cos_theta_max = sqrt(1 - radius * radius / (center - o).squared_length());
		float solid_angle = 2 * M_PI * (1 - cos_theta_max);
		return 1 / solid_angle;
	}
	else
	{
		return 0;
	}
}
vec3 sphere::random(const vec3& o) const
{
	vec3 direction = center - o;
	float distance_sqr = direction.squared_length();
	onb uvw;
	uvw.build_from_w(direction);
	return uvw.local(random_to_sphere(radius, distance_sqr));
}