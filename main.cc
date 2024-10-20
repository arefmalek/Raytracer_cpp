#include <iostream>

#include "types.h"
#include "ray.h"
#include "vec3.h"


Color3 ray_color(const Ray __restrict &r)
{
    const Vec3 dir = unit_vector(r.direction());
    const float blue_offset = 0.5 * (dir.Y() + 1.0f);
    assert(blue_offset <= 1.0f && blue_offset >= 0.0f);
    return ((1.0 - blue_offset) * Color3(1.0f, 1.0f, 1.0f) + blue_offset * Color3(0.5, 0.7, 1.0));
}

int temp()
{

    constexpr U32 kImgWidth = 400;
    constexpr float kAspectRatio = 16.0 / 9.0;
    constexpr U32 kImgHeight = MAX(U32(kImgWidth / kAspectRatio), 1U);

    // Camera.
    constexpr float kFocalLength = 1.0f;
    constexpr Point3 kCameraOrigin = Point3(0.0f, 0.0f, 0.0f);

    // Viewpoint, where we're actually projecting the picture onto.
    constexpr float kViewportHeight = 2.0;
    constexpr float kViewportWidth = kViewportHeight * (float(kImgWidth) / kImgHeight);

    // Viewport along x axis.
    constexpr Vec3 viewport_u = Vec3(kViewportWidth, 0, 0);
    // Viewport along y axis.
    constexpr Vec3 viewport_v = Vec3(0, -kViewportHeight, 0);

    // Vertical per-pixel delta along viewport.
    const Vec3 pixel_delta_u = viewport_u / float(kImgWidth);
    // Horizontal per-pixel delta along viewport.
    const Vec3 pixel_delta_v = viewport_v / float(kImgHeight);

    const Point3 upper_left_viewport_corner = Point3(kFocalLength, 0.0f, 0.0f) - (viewport_u / 2) - (viewport_v / 2);
    
    const Point3 pixel00_loc = upper_left_viewport_corner + 0.5*(pixel_delta_u + pixel_delta_v);

    std::cout << "P3\n"
              << kImgWidth << " " << kImgHeight << "\n255\n";

    for (U32 i_row = 0; i_row < kImgHeight; ++i_row)
    {
        std::clog << "\rNum lines remaining " << (kImgHeight - i_row) << std::flush;
        for (U32 i_col = 0; i_col < kImgWidth; ++i_col)
        {
            const Point3 curr_pixel = pixel00_loc + (pixel_delta_v * i_row) + (pixel_delta_u * i_col);
            const Vec3 direction = curr_pixel - kCameraOrigin;
            const Ray r = Ray(kCameraOrigin, direction);

            const Color3 color = ray_color(r);
            write_color(std::cout, color);
        }
    }
    std::clog << "\ndone!\n"
              << std::flush;
    return 0;
}

int main()
{
    temp();
    return 0;
}