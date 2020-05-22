#pragma once
#include "hitable.h"

class xy_rectangle : public hitable
{
public:
	xy_rectangle() = default;
	xy_rectangle(float _x0, float _x1, float _y0, float _y1, float _k, material* mat)
		: x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mat_ptr(mat) {}
	
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, boundary& box)const;

	float x0, x1, y0, y1, k;
	material *mat_ptr;
};

class xz_rectangle : public hitable
{
public:
	xz_rectangle() = default;
	xz_rectangle(float _x0, float _x1, float _z0, float _z1, float _k, material* mat)
		: x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mat_ptr(mat) {}

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, boundary& box)const;

	float x0, x1, z0, z1, k;
	material* mat_ptr;
};

class yz_rectangle : public hitable
{
public:
	yz_rectangle() = default;
	yz_rectangle(float _y0, float _y1, float _z0, float _z1, float _k, material* mat)
		: y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mat_ptr(mat) {}

	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, boundary& box)const;

	float  y0, y1, z0, z1, k;
	material* mat_ptr;
};