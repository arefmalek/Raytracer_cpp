#ifndef HITABLEH
#define HITABLEH

#include "ray.h"

struct hit_record {
    float t; // time variable
    vec3 p; // incoming point vector
    vec3 normal; // normal vector to the point
};

class hitable {
    public:
        virtual bool hit (const ray& r,
                    float t_min,
                    float t_max,
                    hit_record& rec) const = 0;  
};

#endif
