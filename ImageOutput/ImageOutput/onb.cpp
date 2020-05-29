#include "onb.h"

void onb::build_from_w(const vec3& n)
{
	axis[2] = unit_vector(n);
	vec3 a;
	if (fabs(w().x()) > 0.9)
	{
		a = vec3(0.0f, 1.0f, 0.0f);
	}
	else
	{
		a = vec3(1.0f, 0.0f, 0.0f);
	}
	axis[1] = unit_vector(cross(w(), a));
	axis[0] = cross(w(), v());
}

vec3 random_cosine_direction()
{
	float r1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
	float r2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
	float z = sqrt(1 - r2);
	float phi = 2 * M_PI * r1;
	float x = cos(phi) * 2 * sqrt(r2);
	float y = sin(phi) * 2 * sqrt(r2);
	return vec3(x, y, z);
}