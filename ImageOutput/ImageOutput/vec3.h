#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>

class vec3
{
public:

	vec3() = default;
	vec3(float e0, float e1, float e2):e{ e0,e1,e2 } {}
	inline float x() const { return e[0]; }
	inline float y() const  { return e[1]; }
	inline float z() const  { return e[2]; }
	inline float r() const { return e[0]; }
	inline float g() const { return e[1]; }
	inline float b() const { return e[2]; }

	inline const vec3& operator+() const;
	inline vec3 operator-() const;
	inline float operator[](int i) const { return e[i]; }
	inline float& operator[](int i) { return e[i]; }

	inline vec3& operator+=(const vec3& v2);
	inline vec3& operator-=(const vec3& v2);
	inline vec3& operator*=(const vec3& v2);
	inline vec3& operator/=(const vec3& v2);
	inline vec3& operator*=(const float t);
	inline vec3& operator/=(const float t);

	inline float length() const {
		return sqrt(pow(e[0], 2) + pow(e[1], 2) + pow(e[2], 2));
	}
	inline float squared_length() const{
		return pow(e[0], 2) + pow(e[1], 2) + pow(e[2], 2);
	}
	inline void make_unit_vector();

float e[3];
};

