#include "bvh.h"

int box_compare(const hitable* a, const hitable* b, int axis)
{
	boundary box_left, box_right;
	if (!a->bounding_box(0, 0, box_left) || !b->bounding_box(0, 0, box_right))
	{
		std::cerr << "no bounding box in bvh_node constructor\n";
	}
	if ((box_left).min()[axis] - (box_right).min()[axis] < 0.0f)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}
int box_x_compare(const void* a, const void* b)
{
	return box_compare(*(hitable**)a, *(hitable**)b, 0);
}
int box_y_compare(const void* a, const void* b)
{
	return box_compare(*(hitable**)a, *(hitable**)b, 1);
}
int box_z_compare(const void* a, const void* b)
{
	return box_compare(*(hitable**)a, *(hitable**)b, 2);
}

bvh_node::bvh_node(hitable** l, int n, float time0, float time1)
{
	float random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX + 1);
	int axis = static_cast<int>(3 * random);

	if (axis == 0)
	{
		qsort(l, n, sizeof(hitable*), box_x_compare);
	}
	else if (axis == 1)
	{
		qsort(l, n, sizeof(hitable*), box_y_compare);
	}
	else
	{
		qsort(l, n, sizeof(hitable*), box_z_compare);
	}
	if (n == 1)
	{
		left = right = l[0];
	}
	else if (n == 2)
	{
		left = l[0];
		right = l[1];
	}
	else
	{
		left = new bvh_node(l, n / 2, time0, time1);
		right = new bvh_node(l + n / 2, n - n / 2, time0, time1);
	}

	boundary box_left;
	boundary box_right{};

	if (!left->bounding_box(0.0f, 0.0f, box_left) || !right->bounding_box(0.0f, 0.0f, box_right))
	{
		std::cerr << "no bounding box in bvh_node constructor\n";
	}

	box = surrounding_box(box_left, box_right);

}


bool bvh_node::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	if (box.hit(r, t_min, t_max))
	{
		hit_record left_rec, right_rec;
		bool hit_left = left->hit(r, t_min, t_max, left_rec);
		bool hit_right = right->hit(r, t_min, t_max, right_rec);
		if (hit_left && hit_right)
		{
			if (left_rec.t < right_rec.t)
			{
				rec = left_rec;
			}
			else {
				rec = right_rec;
			}
			return true;
		}
		else if (hit_left)
		{
			rec = left_rec;
			return true;
		}
		else if (hit_right)
		{
			rec = right_rec;
			return true;
		}
		else return false;
	}
	else return false;
}
bool bvh_node::bounding_box(float t0, float t1, boundary& box) const
{
	box = this->box;
	return true;
}