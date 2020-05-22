#pragma once
#include "hitable.h"

class sphere : public hitable
{
public: 
	sphere() = default;
	sphere(vec3 cen, float r, material *mat) : center( cen ) , radius ( r ), mat_ptr(mat) {}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	vec3 center;
	float radius;
	material* mat_ptr;
};

class moving_sphere : public hitable
{
public:
	moving_sphere() = default;
	moving_sphere(vec3 cen0, vec3 cen1, float t0, float t1, float r, material* m)
		: center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), mat_ptr(m) {}
	
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	vec3 center(float time) const;
	vec3 center0, center1;
	float time0, time1;
	float radius;
	material* mat_ptr;
};

