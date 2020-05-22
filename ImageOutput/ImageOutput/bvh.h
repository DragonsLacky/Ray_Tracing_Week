#pragma once
#include "hitable.h"

class bvh_node : public hitable
{
public:
	bvh_node() = default;
	bvh_node(hitable** l, int n, float time0, float time1);
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, boundary& box) const;

	
	hitable* left;
	hitable* right;
	boundary box;
};

int box_compare(const hitable* a, const hitable* b, int axis);
int box_x_compare(const void* a, const void* b);
int box_y_compare(const void* a, const void* b);
int box_z_compare(const void* a, const void* b);