#pragma once
#include "hitable.h"

bool flip_normals::hit(const ray& r, float t_min, float t_max, hit_record& rec) const 
{
	if (ptr->hit(r, t_min, t_max, rec))
	{
		rec.normal = -rec.normal;
		return true;
	}
	else
	{
		return false;
	}
}
bool flip_normals::bounding_box(float t0, float t1, boundary& box)const
{
	return ptr->bounding_box(t0, t1, box);
}