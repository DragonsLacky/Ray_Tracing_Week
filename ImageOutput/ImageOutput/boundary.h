#pragma once
#include <math.h>
#include "ray.h"

inline float ffmin(float a, float b) { return a < b ? a : b; }
inline float ffmax(float a, float b) { return a > b ? a : b; }

class boundary
{
public:
	boundary() = default;
	boundary(const vec3& a, const vec3& b) : _min(a), _max(b) {}

	vec3 min() const { return _min; }
	vec3 max() const { return _max; }

	bool hit(const ray& r, float t_min, float t_max) const;


	vec3 _min;
	vec3 _max;
};

boundary surrounding_box(boundary box0, boundary box1);