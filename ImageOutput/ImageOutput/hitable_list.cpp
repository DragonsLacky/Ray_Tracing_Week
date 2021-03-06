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

bool hitable_list::bounding_box(float t0, float t1, boundary& box) const
{
	if (list_size < 1) return false;

	boundary temp_box;
	bool first_true = list[0]->bounding_box(t0, t1, temp_box);
	if (!first_true) 
	{
		return false;
	}
	else {
		box = temp_box;
	}

	for (int  i = 1; i < list_size; i++)
	{
		if (list[i]->bounding_box(t0, t1, temp_box))
		{
			box = surrounding_box(box, temp_box);
		}
		else return false;
	}

	return true;
}

float hitable_list::pdf_value(const vec3& o, const vec3& v) const
{
	float weight = 1.0 / list_size;
	float sum = 0;
	for (int i = 0; i < list_size; i++)
	{
		sum += weight * list[i]->pdf_value(o, v);
	}
	return sum;
}
vec3 hitable_list::random(const vec3& o) const
{
	float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
	int index = static_cast<int>(random * list_size);
	return list[index]->random(o);
}