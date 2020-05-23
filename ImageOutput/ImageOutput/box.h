#pragma once
#include "hitable_list.h"
#include "rectangle.h"

class box : public hitable
{
public:
	box() = default;
	box(const vec3& p0, const vec3& p1, material* mat);
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, boundary& box)const;
	vec3 p_min, p_max;
	hitable* list_ptr;
};

