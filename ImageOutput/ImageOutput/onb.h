#pragma once
#include "vec3.h"
#include <corecrt_math_defines.h>

class onb
{
public:
	onb() = default;
	vec3 operator[](int i) const { return axis[i]; }
	vec3 u() const { return axis[0]; }
	vec3 v() const { return axis[1]; }
	vec3 w() const { return axis[2]; }
	vec3 local(float a, float b, float c) const { return a * u() + b * v() + c * w(); }
	vec3 local(const vec3& a) const { return a.x() * u() + a.y() * v() + a.z() * w(); }
	void build_from_w(const vec3&);
	vec3 axis[3];
};

vec3 random_cosine_direction();