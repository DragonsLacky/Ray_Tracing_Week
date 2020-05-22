#pragma once
#include "ray.h"

inline float trilinear_iterp(float c[2][2][2], float u, float v, float w);
inline float perlin_interp(vec3 c[2][2][2], float u, float v, float w);

class perlin
{
public:
	float noise(const vec3& p) const;
	float turbulence(const vec3& p, int depth = 7) const;
	static vec3* ranvec;
	static int* perm_x;
	static int* perm_y;
	static int* perm_z;
};

//static float* perlin_generate();
static vec3* perlin_generate();
void permute(int* p, int n);
static int* perlin_generate_perm();

