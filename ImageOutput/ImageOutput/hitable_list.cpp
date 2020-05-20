#pragma once
#include "hitable_list.h"

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	double closest = t_max;
	for (int i = 0; i < list_size; i++)
	{
		if (list[i]->hit(r, t_min, closest, temp_rec))
		{
			hit_anything = true;
			closest = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hit_anything;
}