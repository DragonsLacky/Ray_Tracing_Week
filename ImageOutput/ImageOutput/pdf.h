#pragma once
#include "vec3.h"
#include "onb.h"
#include "hitable.h"
#include <corecrt_math_defines.h>

class pdf
{
public:
	virtual float value(const vec3& direction) const = 0;
	virtual vec3 generate() const = 0;
};

class cosine_pdf : public pdf
{
public:
	cosine_pdf(const vec3& w);
	virtual float value(const vec3& direction) const;
	virtual vec3 generate() const;
	onb uvw;
};

class hittable_pdf : public pdf
{
public:
	hittable_pdf(hitable* p, const vec3& o) : obj(p), origin(o) {}
	virtual float value(const vec3& direction) const;
	virtual vec3 generate() const;
	hitable* obj;
	vec3 origin;
};


class mixture_pdf : public pdf
{
public:
	mixture_pdf(pdf* p0, pdf* p1) { p[0] = p0; p[1] = p1; }
	virtual float value(const vec3& direction) const;
	virtual vec3 generate() const;
	pdf* p[2];
};