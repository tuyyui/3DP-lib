#include <iostream>
#include <fstream>
#include <cmath>

class Vector
{
public:
    Vector() { x = y = z = 0; } //Default Constructor
    Vector(double a, double b, double c) : x(a), y(b), z(c) {}
    Vector operator-(Vector i)
    {
        return Vector(x - i.x, y - i.y, z - i.z);
    }

    //private:
    double x, y, z;
};
double dot(Vector v, Vector b) { return (v.x * b.x + v.y * b.y + v.z * b.z); }
class Ray
{
public:
    Ray(Vector i, Vector j) : origin(i), Direction(j) {}

    //private:
    Vector origin;
    Vector Direction;
};

class Sphere
{
public:
    Sphere(Vector i, double j) : center(i), radius(j) {}

    //private:
    Vector center;
    double radius;

    bool intersect(Ray _ray, double &t)
    {
        Vector o = _ray.origin;
        Vector d = _ray.Direction;
        Vector oc = o - d;
        double b = 2 * dot(oc, d);
        double c = dot(oc, oc) - radius * radius;
        double disc = b * b - 4 * center.y;
        if (disc < 0)
        {
            return false;
        }
        else
            disc = sqrt(disc);
        double T = -b - disc;
        double tt = -b + disc;

        auto _t = (T < tt) ? T : tt;
        return true;
    }
};
struct Color
{
    double r, g, b;
    Color() { r = g = b = 0; }
    Color(double i, double j, double k) : r(i), g(j), b(k) {}
};
int main()
{
    constexpr unsigned int Width = 500;
    constexpr unsigned int Height = 500;

    std::ofstream out("out.ppm");
    out << "P3\n"
        << Width << '\n'
        << Height << '\n'
        << "255\n";

    Color pixel_col[Height][Width];

    Color White(255, 255, 255);
    Sphere sphere(Vector(Width / 2, Height / 2, 50), 20);
    //Looping throug Pixels
    for (int x = 0; x < Width; x++)
    {
        for (int y = 0; y < Height; y++)
        {
            //Sending Ray through Pixel
            Ray ray(Vector(x, y, 0), Vector(0, 0, 1));
            double t = 20000;

            //Intersection check
            if (sphere.intersect(ray, t))
            {
                //Coloring the pixel
                pixel_col[y][x] = White;
            }
            out << pixel_col[y][x].r << std::endl;
            out << pixel_col[y][x].g << std::endl;
            out << pixel_col[y][x].b << std::endl;
        }
    }

    return 0;
}