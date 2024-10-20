#ifndef COLOR_H
#define COLOR_H

#include <stdint.h>
#include <ostream>
#include <cmath>

#include "vec3.h"

using U32 = uint32_t;

using Color3 = Vec3;

#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define MAX(a, b) ((a) > (b)) ? (a) : (b)

constexpr U32 kMaxNumbers = 255;

void write_color(std::ostream &out, const Color3 &color)
{
    const float r = color.X();
    const float g = color.Y();
    const float b = color.Z();

    assert(r <= 1.0f);
    assert(g <= 1.0f);
    assert(b <= 1.0f);
    const U32 ir = MIN(U32(259.99 * r), kMaxNumbers);
    const U32 ig = MIN(U32(259.99 * g), kMaxNumbers);
    const U32 ib = MIN(U32(259.99 * b), kMaxNumbers);
    std::cout << ir << " " << ig << " " << ib << "\n";
}
#endif