#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <cassert>

#define IS_FLOAT_NONZERO(var) (var <= -0.00000001f || var >= 0.00000001f)

struct Vec3
{
    Vec3() : x(0.0f), y(0.0f), z(0.0f)
    {
    }

    constexpr Vec3(float a, float b, float c) : x(a), y(b), z(c)
    {
    }

    float X() const { return x; }
    float Y() const { return y; }
    float Z() const { return z; }

    Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    Vec3 &operator+=(const Vec3 &v)
    {
        x += v.X();
        y += v.Y();
        z += v.Z();
        return *this;
    }

    Vec3 &operator*=(const float t)
    {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }

    Vec3 &operator/=(const float t)
    {
        assert(IS_FLOAT_NONZERO(t));
        return *this *= 1 / t;
    }

    float length_sqr() const
    {
        return x * x + y * y + z * z;
    }

    float magnitude() const
    {
        return std::sqrt(this->length_sqr());
    }

private:
    float x;
    float y;
    float z;
};

using Point3 = Vec3;

inline std::ostream &operator<<(std::ostream &out, const Vec3 &u)
{
    return out << u.X() << ' ' << u.Y() << ' ' << u.Z();
}

inline Vec3 operator+(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.X() + v.X(), u.Y() + v.Y(), u.Z() + v.Z());
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v)
{
    return -u + v;
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.X() * v.X(), u.Y() * v.Y(), u.Z() * v.Z());
}

inline Vec3 operator*(const Vec3 &u, const float t)
{
    return Vec3(u.X() * t, u.Y() * t, u.Z() * t);
}

inline Vec3 operator*(const float t, const Vec3 &u)
{
    return Vec3(u.X() * t, u.Y() * t, u.Z() * t);
}

inline Vec3 operator/(const Vec3 &u, const float t)
{
    assert(IS_FLOAT_NONZERO(t));
    return u * (1 / t);
}

inline Vec3 dot(const Vec3 &u, const Vec3 &v)
{
    return Vec3(u.X() * v.X(), u.Y() * v.Y(), u.Z() * v.Z());
}

inline Vec3 cross(const Vec3 &u, const Vec3 &v)
{
    const float ux = u.X();
    const float uy = u.Y();
    const float uz = u.Z();
    const float vx = v.X();
    const float vy = v.Y();
    const float vz = v.Z();

    /**
     * ux vx (i x i) + ux vy (i x j) + ux vz (i x k) +
     * uy vx (j x i) + uy vy (j x j) + uy vz (j x k) +
     * uz vx (k x i) + uz vy (k x j) + uz vz (k x k) +
     * =
     * ux vy (k) - ux vz (j) -
     * uy vx (k) + uy vz (i) -
     * uz vx (j) - uz vy (i)
     */
    return Vec3(uy * vz - uz * vy, -(ux * vz) + uz * vx, ux * vy - uy * vx);
}

inline Vec3 unit_vector(const Vec3 &u)
{
    return u / u.magnitude();
}

#endif