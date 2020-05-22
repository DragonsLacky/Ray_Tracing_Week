#pragma once
#include "vec3.cpp"
class ray
{
	float _time;
public:
	vec3 A;
	vec3 B;
	ray() = default;
	ray(const vec3& a, const vec3& b, float ti) : A(a), B(b), _time(ti) {}
	vec3 origin() const { return A; }
	float time() const { return _time; };
	vec3 direction() const { return B; }
	vec3 point(float t) const { return A + t * B; }
	
};

