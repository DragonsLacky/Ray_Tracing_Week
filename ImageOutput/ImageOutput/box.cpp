#include "box.h"

box::box(const vec3& p0, const vec3& p1, material* mat)
{
	p_min = p0;
	p_max = p1;

	hitable** list = new hitable * [6];

	list[0] = new xy_rectangle(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), mat);
	list[1] = new flip_normals(new xy_rectangle(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), mat));
	list[2] = new xz_rectangle(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), mat);
	list[3] = new flip_normals(new xz_rectangle(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), mat));
	list[4] = new yz_rectangle(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), mat);
	list[5] = new flip_normals(new yz_rectangle(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), mat));

	list_ptr = new hitable_list(list, 6);

}
bool box::hit(const ray& r, float t_min, float t_max, hit_record& rec) const
{
	return list_ptr->hit(r, t_min, t_max, rec);
}
bool box::bounding_box(float t0, float t1, boundary& box)const
{
	box = boundary(p_min, p_max);
	return true;
}
