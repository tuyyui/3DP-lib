
#include <fstream>
#include <cmath>
#include <iostream>
#include "include/raycastengine.h"
#include "include/ray.h"

struct Vec3
{
    double x, y, z;
    Vec3(double x, double y, double z) : x(x), y(y), z(z) {}
    Vec3 operator+(const Vec3 &v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    Vec3 operator-(const Vec3 &v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    Vec3 operator*(double d) const { return Vec3(x * d, y * d, z * d); }
    Vec3 operator/(double d) const { return Vec3(x / d, y / d, z / d); }
    Vec3 normalize() const
    {
        double mg = sqrt(x * x + y * y + z * z);
        return Vec3(x / mg, y / mg, z / mg);
    }
};
inline double dot(const Vec3 &a, const Vec3 &b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

struct Ray
{
    Vec3 o, d;
    Ray(const Vec3 &o, const Vec3 &d) : o(o), d(d) {}
};

struct Sphere
{
    Vec3 c;
    double r;
    Sphere(const Vec3 &c, double r) : c(c), r(r) {}
    Vec3 getNormal(const Vec3 &pi) const { return (pi - c) / r; }
    bool intersect(const Ray &ray, double &t) const
    {
        const Vec3 o = ray.o;
        const Vec3 d = ray.d;
        const Vec3 oc = o - c;
        const double b = 2 * dot(oc, d);
        const double c = dot(oc, oc) - r * r;
        double disc = b * b - 4 * c;
        if (disc < 1e-4)
            return false;
        disc = sqrt(disc);
        const double t0 = -b - disc;
        const double t1 = -b + disc;
        t = (t0 < t1) ? t0 : t1;
        return true;
    }
};

void clamp255(Vec3 &col)
{
    col.x = (col.x > 255) ? 255 : (col.x < 0) ? 0 : col.x;
    col.y = (col.y > 255) ? 255 : (col.y < 0) ? 0 : col.y;
    col.z = (col.z > 255) ? 255 : (col.z < 0) ? 0 : col.z;
}

vecfloat color(const ray &r)
{
    vecfloat unit_direction(0, 0, 0);
    unit_direction = unit_direction.unit_vector(r.direction());

    float t = 0.5 * (unit_direction.get_y() + 1.0);

    vecfloat a(1.0, 1.0, 1.0);
    vecfloat b(0.5, 0.7, 1.0);

    return (a * (1.0 - t)) + (b * t);
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
    float u = float(20) / float(60);
    float v = float(50) / float(40);
    // Not working as of now due to ray not returning a value.

    ray r(origin, (lower_left_corner + ((_horizontial * u) + (vertical * v))));

    vecfloat col = color(r);

    for (int i = ny - 1; i >= 0; i--)
    {
        for (int j = 0; j < nx; j++)
        {
            float u = float(j) / float(nx);
            float v = float(i) / float(ny);
            // Not working as of now due to ray not returning a value.

            ray r(origin, (lower_left_corner + ((_horizontial * u) + (vertical * v))));
            vecfloat col = color(r);

            int ir = int(255.99 * col.get_x());
            int ig = int(255.99 * col.get_y());
            int ib = int(255.99 * col.get_z());
            out << ir << " " << ig << " " << ib << "\n";
        }
    }

    return 0;
}
