#include "vec3.h"



inline const vec3& vec3::operator+() const 
{
    return *this; 
}

inline vec3 vec3::operator-() const 
{
    return vec3(-e[0], -e[1], -e[2]); 
}

inline std::istream& operator>> (std::istream &is, vec3 &v)
{
    is >> v.e[0] >> v.e[1] >> v.e[2];
    return is;
}

inline std::ostream& operator<< (std::ostream& os, vec3& v)
{
    os << v.e[0] << v.e[1] << v.e[2];
    return os;
}

inline void vec3::make_unit_vector()
{
    float k = 1.0 / length();
    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
}

inline vec3 operator+(const vec3& v1, const vec3& v2)
{
    return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline vec3 operator-(const vec3& v1, const vec3& v2)
{
    return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

inline vec3 operator*(const vec3& v1, const vec3& v2)
{
    return vec3(v1.x() * v2.x(), v1.y() * v2.y(),  v1.z() * v2.z());
}

inline vec3 operator/(const vec3& v1, const vec3& v2)
{
    return vec3(v1.x()/ v2.x(), v1.y() / v2.y(),  v1.z() / v2.z());
}

inline vec3 operator*(float t, const vec3& v)
{
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator/(float t, const vec3& v)
{
    return vec3(t / v.x(), t / v.y(), t / v.z());
}

inline vec3 operator*(const vec3& v, float t)
{
    return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator/(const vec3& v ,float t)
{
    return vec3(t / v.x(), t / v.y(), t / v.z());
}

inline float dot(const vec3& v1, const vec3& v2)
{
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

inline vec3 cross(const vec3& v1, const vec3& v2)
{
    return vec3(v1.y() * v2.z() - v1.z() * v2.y(), 
                -(v1.x()* v2.z() - v1.z() * v2.x()),
                v1.x()* v2.y() - v1.y() * v2.x());
}

inline vec3& vec3::operator+=(const vec3& v) 
{
    *this = *this + v;
    return *this;
}

inline vec3& vec3::operator*=(const vec3& v)
{
    *this = *this * v;
    return *this;
}

inline vec3& vec3::operator/=(const vec3& v)
{
    *this = *this / v;
    return *this;
}

inline vec3& vec3::operator-=(const vec3& v)
{
    *this = *this - v;
    return *this;
}

inline vec3& vec3::operator*=(const float t)
{
    *this = *this * t;
    return *this;
}

inline vec3& vec3::operator/=(const float t)
{
    *this = *this / t;
    return *this;
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}