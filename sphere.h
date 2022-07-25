#ifndef SPHEREH
#define SPHEREH

#include "hitable.h"


class sphere: public hitable {
    public: 
        sphere() {}
        sphere(vec3 ven, float r)  : center(cen), radius(r) {};
        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
        vec3 center;
        float radius;
}



#endif
