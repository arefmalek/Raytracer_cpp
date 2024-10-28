#ifndef SPHERE_H
#define SPHERE_H

#include "rtweekend.h"
#include "hittable.h"

class Sphere : public hittable
{
public:
    Sphere(const Point3 &center, const float radius) : center(center), radius(std::fmax(0.0f, radius))
    {
    }

    bool hit(const Ray &r, const interval ray_interval, hit_record &hit) const override
    {
        const Vec3 oc = center - r.origin();
        const float a = dot(r.direction(), r.direction());
        const float h = dot(r.direction(), oc);
        const float c = dot(oc, oc) - radius * radius;
        const float discriminant = h * h - a * c;

        if (discriminant < 0)
        {
            return false;
        }

        const float sqrtd = std::sqrt(discriminant);

        float root = (h - sqrtd) / a;
        if (!ray_interval.contains(root))
        {
            root = (h + sqrtd) / a;
            if (!ray_interval.contains(root))
            {
                return false;
            }
        }

        hit.p = r.at(root);
        hit.t = root;
        Vec3 outward_normal = (r.at(root) - center) / radius;
        hit.set_normal(r, outward_normal);

        return true;
    }

private:
    Point3 center;
    float radius;
};

#endif