#pragma once
#include "vec3.cpp"
class ray
{
public:
	vec3 A;
	vec3 B;
	ray() = default;
	ray(const vec3& a, const vec3& b) { A = a; B = b; }
	vec3 origin() const { return A; }
	vec3 direction() const { return B; }
	vec3 point(float t) const { return A + t * B; }
};

