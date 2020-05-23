#pragma once
#include "hitable.h"

class translate : public hitable
{
public:
	translate(hitable* p, const vec3& displacement) : obj(p), offset(displacement) {}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, boundary& box)const;

	hitable* obj;
	vec3 offset;

};

class rotate_y : public hitable
{
public:
	rotate_y(hitable* p, float angle);
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, boundary& box)const;
	hitable* obj;
	float sin_theta;
	float cos_theta;
	bool hasbox;
	boundary b_box;
};