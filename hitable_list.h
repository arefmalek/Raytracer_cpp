#ifndef HITABLELISTH
#define HITABLELISTH


#include "hitable.h"

class hitable_list: public hitable {
    public: 
        // class declarations
        hitable_list() {}
        hitable_list(hitable **l, int n) {list = l; list_size = n;}

        // function declarations
        virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;

        // attributes
        hitable **list; // array of hitable pointers
        int list_size; // size of the array
};


bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    hit_record temp_rec;

    bool hit_anything = false;
    double closest_so_far = t_max;

    // for each hitable element
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif