#include "rtweekend.h"

#include "hittable_list.h"
#include "hittable.h"
#include "sphere.h"
#include "camera.h"

int temp()
{
    // Objects in world
    hittable_list world_objects;
    world_objects.add(std::make_shared<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.5f));
    world_objects.add(std::make_shared<Sphere>(Point3(0.5f, 1.0f, -2.0f), 0.2f));
    world_objects.add(std::make_shared<Sphere>(Point3(0.0f, -100.5f, -2.0f), 100.0f));

    Camera cam;
    cam.kImgWidth = 400U;
    cam.kAspectRatio = 16.0f / 9.0f;
    cam.num_samples = 100;
    cam.render(world_objects);

    

    std::clog << "\ndone!\n"
              << std::flush;
    return 0;
}

int main()
{
    temp();
    return 0;
}