#ifndef RTWEEKEND_H
#define RTWEEKEND_H


#include <cmath>
#include <iostream>
#include <random>
#include <limits>
#include <memory>


// File constants.
constexpr float infinity = std::numeric_limits<float>::infinity();
constexpr float kPI = 3.14159265f;

// Utility functions.
inline float degrees_to_radians(float degrees)
{
    return degrees * kPI / 180.0f;
}

inline float radians_to_degrees(float radians)
{
    return radians * 180.0f  / kPI;
}

inline float random_float()
{
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator;
    return distribution(generator);
}

#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define MAX(a, b) ((a) > (b)) ? (a) : (b)

#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "interval.h"

#endif