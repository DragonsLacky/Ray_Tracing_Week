#pragma once

#include "ray.h"
#include <corecrt_math_defines.h>

vec3 random_in_unit_disk();

class camera
{
public:
	camera(vec3 look_from, vec3 look_at, vec3 v_up, float v_fov, float aspect, float aperture, float focus_dist);
	ray get_ray(float u, float v);
	
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	float lens_radius;
};

