#ifndef COLOR_H
#define COLOR_H

#include "rtweekend.h"
#include "interval.h"

#include <stdint.h>
#include <cassert>

using U32 = uint32_t;

using Color3 = Vec3;

constexpr U32 kMaxNumbers = 256;

void write_color(std::ostream &out, const Color3 &color)
{
    const float r = color.X();
    const float g = color.Y();
    const float b = color.Z();

    static const interval intensity(0.0f, 0.999f);
    const U32 ir = U32(kMaxNumbers * intensity.clamp(r));
    const U32 ig = U32(kMaxNumbers * intensity.clamp(g));
    const U32 ib = U32(kMaxNumbers * intensity.clamp(b));
    std::cout << ir << " " << ig << " " << ib << "\n";
}
#endif