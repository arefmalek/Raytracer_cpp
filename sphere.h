#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"


class sphere: public hitable {
    public: 
        sphere() {}
        sphere(vec3 cen, float r)  : center(cen), radius(r) {};
        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
        vec3 center;
        float radius;
};

bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center; 

    // todo: review how we get a, b, c
    float a = dot(r.direction(), r.direction());
    float b = dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;

    float discriminant = b*b - a*c;

    // roots are real, not imaginary
    if (discriminant > 0) {
        float temp = (-b - sqrt(b*b - a*c)) / a; // lower result of quadratic formula
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }

        temp = (-b + sqrt(b*b - a*c)) / a; // higher result of quadratic formula
        if (temp < t_max && temp > t_min) {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            return true;
        }
        
    }

    // neither of the roots were touched, we didn't hit the thing
    return false;
}


#endif
