
#include <fstream>
#include <cmath>
#include <iostream>
#include <memory>
#include "include/raycastengine.h"

#include "include/sphere.h"

#include "include/hittablelist.h"

vecfloat color(const ray &r, hittable *world)
{
    hit_record rec;
    //vecfloat unit_direction(0, 0, 0);
    // unit_direction = unit_direction.unit_vector(r.direction());

    // float t = 0.5 * (unit_direction.get_y() + 1.0);
    if (world->hit(r, 0.0, 100.0f, rec))
    {
        return vecfloat(rec.normal.get_x() + 1, rec.normal.get_y() + 1, rec.normal.get_z() + 1) * (float)0.5;
    }
    else
    {
        vecfloat unit_direction(0, 0, 0);
        unit_direction.unit_vector(r.direction());
        float t = 0.5 * (rec.normal.get_x() + 1.0);
        return vecfloat(1.0, 1.0, 1.0) * (float)(1.0 - t) + vecfloat(0.5, 0.7, 1.0) * t;
    }
}

int main()
{

    int nx = 200;
    int ny = 100;
    std::ofstream out("out.ppm");

    out << "P3\n"
        << nx << " " << ny << "\n255\n";

    vecfloat lower_left_corner(-2.0, -1.0, -1.0);
    vecfloat _horizontial(4.0, 0.0, 0.0);
    vecfloat vertical(0.0, 2.0, 0.0);
    vecfloat origin(0.0, 0.0, 0.0);
    hittable *list[2];
    vecfloat a1(0, 0, 1);
    vecfloat a2(0, -100.5, -1);
    list[0] = new sphere(a1, 0.5);
    list[1] = new sphere(a2, 100);
    hittable *world = new hittable_list(list, 2);

    // Not working as of now due to ray not returning a value.

    for (int i = ny - 1; i >= 0; i--)
    {
        for (int j = 0; j < nx; j++)
        {
            float u = float(j) / float(nx);
            float v = float(i) / float(ny);
            // Not working as of now due to ray not returning a value.

            ray r(origin, (lower_left_corner + ((_horizontial * u) + (vertical * v))));
            vecfloat col = color(r, world);

            int ir = int(255.99 * col.get_x());
            int ig = int(255.99 * col.get_y());
            int ib = int(255.99 * col.get_z());
            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}
