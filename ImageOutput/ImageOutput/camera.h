#pragma once

#include "ray.h"
#include <corecrt_math_defines.h>

class camera
{
public:
	camera(vec3 look_from,vec3 look_at, vec3 v_up, float v_fov, float aspect)
	{
		vec3 u, v, w;

		float theta = v_fov * M_PI / 180;
		float half_height = tan(theta / 2);
		float half_width = aspect * half_height;
		
		origin = look_from;
		
		w = unit_vector(look_from - look_at);
		u = unit_vector(cross(v_up, w));
		v = cross(w, u);

		lower_left_corner = vec3(-half_width, -half_height, -1.0f);
		lower_left_corner = origin - half_width * u - half_height * v - w;
		vertical = 2 * half_height * v;
		horizontal = 2 * half_width * u;
	}
	ray get_ray(float u, float v);
	
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};

