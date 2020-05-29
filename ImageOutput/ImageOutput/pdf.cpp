#include "pdf.h"


cosine_pdf::cosine_pdf(const vec3& w) 
{
    uvw.build_from_w(w); 
}
float cosine_pdf::value(const vec3& direction) const
{
    float cosine = dot(unit_vector(direction), uvw.w());
    if (cosine > 0)
    {
        return cosine / M_PI;

    }
    else
    {
        return 0;
    }
}
vec3 cosine_pdf::generate() const 
{
    return uvw.local(random_cosine_direction());
}

float hittable_pdf::value(const vec3& direction) const
{
    return obj->pdf_value(origin, direction);
}
vec3 hittable_pdf::generate() const
{
    return obj->random(origin);
}
