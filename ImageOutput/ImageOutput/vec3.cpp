#pragma once
#include "vec3.h"



const vec3& vec3::operator+() const 
{
    return *this; 
}

vec3 vec3::operator-() const 
{
    return vec3(-e[0], -e[1], -e[2]); 
}

std::istream& operator>> (std::istream &is, vec3 &v)
{
    is >> v.e[0] >> v.e[1] >> v.e[2];
    return is;
}

std::ostream& operator<< (std::ostream& os, vec3& v)
{
    os << v.e[0] << v.e[1] << v.e[2];
    return os;
}

void vec3::make_unit_vector()
{
    float k = 1.0 / length();
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

vec3 operator+(const vec3& v1, const vec3& v2)
{
    return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

vec3 operator-(const vec3& v1, const vec3& v2)
{
    return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

vec3 operator*(const vec3& v1, const vec3& v2)
{
    return vec3(v1.x() * v2.x(), v1.y() * v2.y(),  v1.z() * v2.z());
}

vec3 operator/(const vec3& v1, const vec3& v2)
{
    return vec3(v1.x()/ v2.x(), v1.y() / v2.y(),  v1.z() / v2.z());
}

vec3 operator*(float t, const vec3& v)
{
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

vec3 operator/(const vec3& v ,float t)
{
    return vec3(v.x() / t,v.y() / t, v.z() / t);
}

vec3 operator*(const vec3& v, float t)
{
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

float dot(const vec3& v1, const vec3& v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

vec3 cross(const vec3& v1, const vec3& v2)
{
    return vec3(v1.y() * v2.z() - v1.z() * v2.y(), 
                -(v1.x()* v2.z() - v1.z() * v2.x()),
                v1.x()* v2.y() - v1.y() * v2.x());
}

vec3& vec3::operator+=(const vec3& v) 
{
    *this = *this + v;
    return *this;
}

vec3& vec3::operator*=(const vec3& v)
{
    *this = *this * v;
    return *this;
}

vec3& vec3::operator/=(const vec3& v)
{
    *this = *this / v;
    return *this;
}

vec3& vec3::operator-=(const vec3& v)
{
    *this = *this - v;
    return *this;
}

vec3& vec3::operator*=(const float t)
{
    *this = *this * t;
    return *this;
}

vec3& vec3::operator/=(const float t)
{
    *this = *this / t;
    return *this;
}

vec3 unit_vector(vec3 v)
{
    return v / v.length();
}

vec3 de_nan(const vec3& c)
{
    vec3 tmp = c;
    if (!(tmp[0] == tmp[0])) tmp[0] = 0;
    if (!(tmp[1] == tmp[1])) tmp[1] = 0;
    if (!(tmp[2] == tmp[2])) tmp[2] = 0;
    return tmp;
}