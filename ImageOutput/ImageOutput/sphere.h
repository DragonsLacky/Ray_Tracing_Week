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

