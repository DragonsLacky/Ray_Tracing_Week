#pragma once
#include "ray.h"
#include "boundary.h"

class material;

struct hit_record
{
	float t;
	float u;
	float v;

	vec3 p;
	vec3 normal;

	bool face;

	material *mat_ptr;
};

inline void set_face(const ray& r, const vec3& outward_normal, hit_record& record)
{
	record.face = dot(r.direction(), outward_normal) < 0;
	record.normal = record.face ? outward_normal : -outward_normal;
}
class hitable
{
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
	virtual bool bounding_box(float t0, float t1, boundary& box)const = 0;
	virtual float pdf_value(const vec3& o, const vec3& v) const { return 0.0f; }
	virtual vec3 random(const vec3& o) const { return vec3(1.0f, 0.0f, 0.0f); }
};

class flip_normals : public hitable
{
public:
	flip_normals(hitable* p) : ptr(p) {}
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
	virtual bool bounding_box(float t0, float t1, boundary& box)const;
	hitable* ptr;
};
