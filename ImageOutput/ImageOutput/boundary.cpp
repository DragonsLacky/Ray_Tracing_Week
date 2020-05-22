#include "boundary.h"

//bool boundary::hit(const ray& r, float t_min, float t_max)
//{
//	for (int i = 0; i < 3; i++)
//	{
//		float invD = 1.0f / r.direction()[i];
//		float t0 = min()[i] - r.origin()[i] * invD; //ffmin((_min[i] - r.origin()[i]) / r.direction()[i], (_max[i] - r.origin()[i]) / r.direction()[i]);
//		float t1 = max()[i] - r.origin()[i] * invD; //ffmax((_min[i] - r.origin()[i]) / r.direction()[i], (_max[i] - r.origin()[i]) / r.direction()[i]);
//		if (invD < 0.0f)
//		{
//			std::swap(t0, t1);
//		}
//		
//		t_min = ffmax(t0, t_min);
//		t_max = ffmin(t1, t_max);
//		if (t_max <= t_min) {
//			return false;
//		}
//	}
//	return true;
//}

boundary surrounding_box(boundary box0, boundary box1)
{
	vec3 small(fmin(box0.min().x(), box1.min().x()), fmin(box0.min().y(), box1.min().y()), fmin(box0.min().z(), box1.min().z()));
	vec3 big(fmax(box0.max().x(), box1.max().x()), fmax(box0.max().y(), box1.max().y()), fmax(box0.max().z(), box1.max().z()));

	return boundary(small, big);
}

bool boundary::hit(const ray& r, float t_min, float t_max) const
{
	for (int i = 0; i < 3; i++)
	{
		float t0 = ffmin((_min[i] - r.origin()[i]) / r.direction()[i], (_max[i] - r.origin()[i]) / r.direction()[i]);
		float t1 = ffmax((_min[i] - r.origin()[i]) / r.direction()[i], (_max[i] - r.origin()[i]) / r.direction()[i]);
		t_min = ffmax(t0, t_min);
		t_max = ffmin(t1, t_max);
		if (t_max <= t_min) 
		{
			return false;
		}
	}
	return true;
}