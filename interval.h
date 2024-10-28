#ifndef INTERVAL_H
#define INTERVAL_H

#include "rtweekend.h"

class interval {
    public:
        float min;
        float max;

        interval(): min(+infinity), max(-infinity)
        {}

        interval(float t_min, float t_max): min(t_min), max(t_max){}

        inline float size() {
            return max - min;
        }

        inline bool contains(const float t_val) const {
            return t_val >= min && max >= t_val;
        }

        inline bool surrounds(const float t_val) const {
            return t_val >= min && max >= t_val;
        }

        float clamp(float x) const
        {
            if (x < min) return min;
            else if (x > max) return max;
            return x;
        }
    
        static const interval empty;
        static const interval universe;
};

const interval interval::empty = interval();
const interval interval::universe = interval(-infinity, infinity);

#endif