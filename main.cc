#include <iostream>

#include "types.h"
#include "ray.h"
#include "vec3.h"
#include "sphere.h"

float hit_sphere(const Point3 __restrict &sphere_center, const float radius, const Ray __restrict r)
{
    const Vec3 origin_center = sphere_center - r.origin();
    const float a = dot(r.direction(), r.direction());
    const float h = dot(r.direction(), origin_center);
    const float c = dot(origin_center, origin_center) - radius * radius;
    const float discriminant = h*h - a * c;

    if (discriminant < 0.0f)
    {
        return -1.0f;
    }

    const float t = (h - std::sqrt(discriminant)) / a;
    return t;
}

Color3 ray_color(const Ray __restrict &r)
{
    const Point3 sphere_origin = Point3(0.0f, 0.0f, -1.0f);
    const float radius = 0.5f;
    const float t = hit_sphere(sphere_origin, radius, r);
    if (t > 0.0f)
    {
        const Vec3 sphere_normal = unit_vector(r.at(t) - sphere_origin);
        return 0.5 * Vec3(sphere_normal.X() + 1.0f, sphere_normal.Y() + 1.0f, sphere_normal.Z() + 1.0f);
    }
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

    const Point3 upper_left_viewport_corner = kCameraOrigin - Vec3(0.0f, 0.0f, kFocalLength) - (viewport_u / 2) - (viewport_v / 2);

    const Point3 pixel00_loc = upper_left_viewport_corner + 0.5 * (pixel_delta_u + pixel_delta_v);



    std::cout << "P3\n"
              << kImgWidth << " " << kImgHeight << "\n255\n";

    for (U32 i_row = 0; i_row < kImgHeight; ++i_row)
    {
        std::cout << "\rNum lines remaining " << (kImgHeight - i_row) << std::flush;
        for (U32 i_col = 0; i_col < kImgWidth; ++i_col)
        {
            const Point3 curr_pixel = pixel00_loc + (pixel_delta_u * i_col) + (pixel_delta_v * i_row);
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