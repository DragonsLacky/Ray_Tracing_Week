#pragma once

#include "ray.h"

class camera
{
public:
	camera()
	{
		origin = vec3(0.0f, 0.0f, 0.0f);
		lower_left_corner = vec3(-2.0f, -1.0f, -1.0f);
		vertical = vec3(0.0f, 2.0f, 0.0f);
		horizontal = vec3(4.0f, 0.0f, 0.0f);
	}
	ray get_ray(float u, float v);
	
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};

