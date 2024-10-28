#ifndef HITTABLE_LIST
#define HITTABLE_LIST

#include "rtweekend.h"
#include "hittable.h"

#include <vector>


class hittable_list: public hittable
{
    public:
        std::vector < std::shared_ptr<hittable>> hittable_objects;

        hittable_list() {}
        hittable_list(std::shared_ptr<hittable> hittable_obj) {
            add(hittable_obj);
        }

        void clear()
        {
            hittable_objects.clear();
        }

        void add(std::shared_ptr<hittable> hittable_obj)
        {
            hittable_objects.push_back(hittable_obj);
        }

        bool hit(const Ray& r, const interval ray_interval, hit_record& hit) const override
        {
            bool hit_anything = false;
            float closest_t = infinity;
            hit_record temp_hit;

            for (std::shared_ptr<hittable> hittable_obj: hittable_objects)
            {
                if (hittable_obj->hit(r, ray_interval, temp_hit) && temp_hit.t <= closest_t)
                {
                    hit_anything = true;
                    hit = temp_hit;
                    closest_t = hit.t;
                }
            }

            return hit_anything;
        }
};


#endif