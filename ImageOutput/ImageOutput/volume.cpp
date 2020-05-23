#include "volume.h"

bool constant_volume::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);

	bool db = (random < 0.00001);
	db = false;
	hit_record rec1, rec2;
	if (bounds->hit(r, FLT_MIN, FLT_MAX, rec1))
	{
		if (bounds->hit(r, rec1.t + 0.0001, FLT_MAX, rec2))
		{
			if (db)
			{
				std::cerr << "\nt0 t1 " << rec1.t << " " << rec2.t << "\n";
			}
			if (rec1.t < t_min) rec1.t = t_min;
			if (rec2.t > t_max) rec2.t = t_max;
			if (rec1.t >= rec2.t) return false;

			if (rec1.t < 0) rec1.t = 0;

			float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
			float distance_inside_boundary = (rec2.t - rec1.t) * r.direction().length();
			float hit_distance = -(1 / density) * log(random);

			if (hit_distance < distance_inside_boundary)
			{
				if (db) std::cerr << "hit_distance =" << hit_distance << "\n";
				rec.t = rec1.t + hit_distance / r.direction().length();
				if (db) std::cerr << "rec.t =" << rec.t << "\n";
				rec.p = r.point(rec.t);
				if (db) std::cerr << "rec.p =" << rec.p << "\n";
				rec.normal = vec3(1, 0, 0);
				rec.mat_ptr = phase_function;
				return true;
			}
		}
	}
	return false;
}

bool constant_volume::bounding_box(float t0, float t1, boundary& box) const
{
	return bounds->bounding_box(t0, t1, box);
}
