#pragma once
#include "hitable.h"
#include "texture.h"
#include "material.h"

class constant_volume : public hitable
{
public:
	constant_volume(hitable* h, float d, texture* t) : bounds(h), density(d) { phase_function = new isotropic(t); }
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, boundary& box)const;
	hitable* bounds;
	float density;
	material* phase_function;
};

