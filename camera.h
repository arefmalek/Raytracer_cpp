#ifndef CAMERA_H
#define CAMERA_H

#include "hittable_list.h"

class Camera {
    public:
        U32 kImgWidth = 100;
        float kAspectRatio = 1.0;
        U32 num_samples = 10;

        void render(const hittable_list& __restrict world_objects)
        {
            initiailize();
            std::cout << "P3\n"
                      << kImgWidth << " " << kImgHeight << "\n" << kMaxNumbers << "\n";

            for (U32 i_row = 0; i_row < kImgHeight; ++i_row)
            {
                std::clog << "\rNum lines remaining " << (kImgHeight - i_row) << "\n" << std::flush;
                for (U32 i_col = 0; i_col < kImgWidth; ++i_col)
                {
                    Color3 total_color = Color3(0.0f, 0.0f, 0.0f) ;
                    for (U32 i_sample = 0; i_sample < num_samples; ++i_sample)
                    {
                        Ray curr_ray = get_ray(i_row, i_col);
                        const Color3 color = ray_color(curr_ray, world_objects);
                        total_color += color;
                    }
                    // average out values
                    total_color /= num_samples;

                    write_color(std::cout, total_color);
                }
            }
        }

    private:
        const float kFocalLength = 1.0f;
        // Camera.
        const Point3 kCameraOrigin = Point3(0.0f, 0.0f, 0.0f);

        // Viewpoint, where we're actually projecting the picture onto.
        const float kViewportHeight = 2.0;

        U32 kImgHeight;
        Vec3 pixel00_loc;
        Vec3 pixel_delta_u;
        Vec3 pixel_delta_v;
        
        Ray get_ray(U32 row, U32 col)
        {
            const Vec3 pixel_offset = sample_random();
            const Point3 curr_pixel = pixel00_loc + (pixel_delta_u * (col + pixel_offset.X())) + (pixel_delta_v * (row + pixel_offset.Y()));
            const Vec3 direction = curr_pixel - kCameraOrigin;
            const Ray r = Ray(kCameraOrigin, direction);
            return r;
        }

        Vec3 sample_random() const
        {
            return Vec3(random_float() - 0.5f, random_float() - 0.5f, 0);
        }

        void initiailize() {
            this->kImgHeight = MAX(U32(kImgWidth / kAspectRatio), 1U);

            const float kViewportWidth = kViewportHeight * (float(kImgWidth) / kImgHeight);

            // Viewport along x axis.
            const Vec3 viewport_u = Vec3(kViewportWidth, 0, 0);
            // Viewport along y axis.
            const Vec3 viewport_v = Vec3(0, -kViewportHeight, 0);

            // Vertical per-pixel delta along viewport.
            this->pixel_delta_u = viewport_u / float(kImgWidth);
            // Horizontal per-pixel delta along viewport.
            this->pixel_delta_v = viewport_v / float(kImgHeight);

            const Point3 upper_left_viewport_corner = kCameraOrigin - Vec3(0.0f, 0.0f, kFocalLength) - (viewport_u / 2) - (viewport_v / 2);

            this->pixel00_loc = upper_left_viewport_corner + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

        Color3 ray_color(const Ray __restrict &r, const hittable_list &__restrict world_objects)
        {
            hit_record intersection;

            if (world_objects.hit(r, interval(0, infinity), intersection))
            {
                return 0.5f * (intersection.surface_normal + Vec3(1.0f, 1.0f, 1.0f));
            }
            else
            {
                const Vec3 dir = unit_vector(r.direction());
                const float blue_offset = 0.5 * (dir.Y() + 1.0f);
                assert(blue_offset <= 1.0f && blue_offset >= 0.0f);
                return ((1.0 - blue_offset) * Color3(1.0f, 1.0f, 1.0f) + blue_offset * Color3(0.5, 0.7, 1.0));
            }
        }
};

#endif