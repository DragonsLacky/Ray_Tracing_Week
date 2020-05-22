#include "camera.h"

vec3 random_in_unit_disk()
{
	vec3 p;

	do {
		float random1 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1.0);
		float random2 = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1.0);

		p = 2.0f * vec3(random1, random2, 0) - vec3(1.0f, 1.0f, 0.0f);
	} while (dot(p, p) >= 1.0f);
	return p;
}

ray camera::get_ray(float s, float t)
{
	vec3 rd = lens_radius * random_in_unit_disk();
	vec3 offset = u * rd.x() + v * rd.y();
	float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
	float time = time0 + random * (time1 - time0);
	return ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset, time);
}

camera::camera(vec3 look_from, vec3 look_at, vec3 v_up, float v_fov, float aspect, float aperture, float focus_dist,float t0, float t1)
{
	lens_radius = aperture / 2;

	float theta = v_fov * M_PI / 180;
	float half_height = tan(theta / 2);
	float half_width = aspect * half_height;

	origin = look_from;

	w = unit_vector(look_from - look_at);
	u = unit_vector(cross(v_up, w));
	v = cross(w, u);

	time0 = t0;
	time1 = t1;

	//lower_left_corner = vec3(-half_width, -half_height, -1.0f);
	lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
	vertical = 2 * half_height * focus_dist * v;
	horizontal = 2 * half_width * focus_dist * u;
}