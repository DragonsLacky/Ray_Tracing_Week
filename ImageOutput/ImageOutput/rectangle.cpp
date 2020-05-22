#include "rectangle.h"

bool xy_rectangle::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	float t = (k - r.origin().z()) / r.direction().z();
	if (t < t_min || t > t_max)
	{
		return false;
	}
	float x = r.origin().x() + t * r.direction().x();
	float y = r.origin().y() + t * r.direction().y();

	if (x < x0 || x > x1 || y < y0 || y > y1)
	{
		return false;
	}

	rec.u = (x - x0) / (x1 - x0);
	rec.v = (y - y0) / (y1 - y0);

	rec.t = t;

	rec.mat_ptr = mat_ptr;
	rec.p = r.point(t);
	rec.normal = vec3(0.0f, 0.0f, 1.0f);
	return true;

}
bool xy_rectangle::bounding_box(float t0, float t1, boundary& box)const
{
	box = boundary(vec3(x0, y0, k - 0.0001), vec3(x1, y1, k + 0.0001));
	return true;
}
