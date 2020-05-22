#pragma once
#include "sphere.h"


void get_sphere_uv(const vec3& p, float& u, float& v)
{
	float phi = atan2(p.z(), p.x());
	float theta = asin(p.y());

	u = 1 - (phi + M_PI) / (2 * M_PI);
	v = (theta + M_PI / 2) / M_PI;
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

