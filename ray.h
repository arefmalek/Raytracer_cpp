#ifndef RAY_H
#define RAY_H

#include "vec3.h"

struct Ray
{
    Ray() {}
    Ray(const Point3 &origin, const Vec3 &direction) : orig(origin), linear_scale(direction)
    {
    }

    const Point3 &origin() const { return orig; }
    const Vec3 &direction() const { return linear_scale; }

    Point3 at(float t) const
    {
        return orig + linear_scale * t;
    }

private:
    Point3 orig;
    Vec3 linear_scale;
};

#endif