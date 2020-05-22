#pragma once
#include "sphere.h"

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
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = mat_ptr;
			return true;
		}
		
		temp = (-b + sqrt(discriminant)) / a;

		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.point(rec.t);
			rec.normal = (rec.p - center) / radius;
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