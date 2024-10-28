#ifndef HITTABLE_H
#define HITTABLE_H

#include "rtweekend.h"

struct hit_record
{
    Point3 p;
    float t;
    Vec3 surface_normal;
    bool front_face;

    void set_normal(const Ray &incident, const Vec3 &center_normal)
    {
        assert(center_normal.magnitude() > 0.999f && center_normal.magnitude() < 1.001f);
        front_face = dot(incident.direction(), center_normal) < 0.0f;
        surface_normal = front_face ? center_normal : -center_normal;
    }
};

class hittable
{
public:
    virtual ~hittable() = default;

    virtual bool hit(const Ray &r, const interval ray_interval, hit_record &hit) const = 0;
};

#endif