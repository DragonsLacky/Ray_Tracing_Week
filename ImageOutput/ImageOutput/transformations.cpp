#include "transformations.h"
#include <corecrt_math_defines.h>

bool translate::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	ray moved_r(r.origin() - offset, r.direction(), r.time());
	if (obj->hit(moved_r, t_min, t_max, rec))
	{
		rec.p += offset;
		return true;
	}
	else return false;
}
bool translate::bounding_box(float t0, float t1, boundary& box)const
{
	if (obj->bounding_box(t0, t1, box))
	{
		box = boundary(box.min() + offset, box.max() + offset);
		return true;
	}
	else return false;
}

rotate_y::rotate_y(hitable* p, float angle)
{
	obj = p;
	float angle_radians = (M_PI / 180.0) * angle;
	sin_theta = sin(angle_radians);
	cos_theta = cos(angle_radians);
	hasbox = obj->bounding_box(0.0f, 1.0f, b_box);
	vec3 min(FLT_MAX, FLT_MAX, FLT_MAX);
	vec3 max(-FLT_MAX, -FLT_MAX, -FLT_MAX);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				float x = i * b_box.max().x() + (1 - i) * b_box.min().x();
				float y = j * b_box.max().y() + (1 - j) * b_box.min().y();
				float z = k * b_box.max().z() + (1 - k) * b_box.min().z();

				float x_new = cos_theta * x + sin_theta * z;
				float z_new = -sin_theta * x + cos_theta * z;

				vec3 tmp(x_new, y, z_new);
				for (int c = 0; c < 3; c++)
				{
					if (tmp[c] > max[c])
					{
						max[c] = tmp[c];
					}
					if (tmp[c] < min[c])
					{
						min[c] = tmp[c];
					}
				}
			}
		}
	}
	b_box = boundary(min, max);
}
bool rotate_y::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	vec3 origin = r.origin();
	vec3 direction = r.direction();
	origin[0] = cos_theta * r.origin().x() - sin_theta * r.origin().z();
	origin[2] = sin_theta * r.origin().x() + cos_theta * r.origin().z();
	
	direction[0] = cos_theta * r.direction().x() - sin_theta * r.direction().z();
	direction[2] = sin_theta * r.direction().x() + cos_theta * r.direction().z();

	ray rotated(origin, direction, r.time());
	
	if (obj->hit(rotated, t_min, t_max, rec))
	{
		vec3 p = rec.p;
		vec3 normal = rec.normal;
		p[0] = cos_theta * rec.p.x() + sin_theta * rec.p.z();
		p[2] = -sin_theta * rec.p.x() + cos_theta * rec.p.z();
		normal[0] = cos_theta * rec.normal.x() + sin_theta * rec.normal.z();
		normal[2] = -sin_theta * rec.normal.x() + cos_theta * rec.normal.z();
		rec.p = p;
		rec.normal = normal;
		return true;
	}
	else return false;
}
bool rotate_y::bounding_box(float t0, float t1, boundary& box)const
{
	box = b_box; 
	return hasbox;
}
