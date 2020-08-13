
#ifndef RAYCASTENGINE_H
#define RAYCASTENGINE_H
#include <iostream>
#include <cmath>
#include <vector>
//RayCaster engine
namespace raycast
{
    template <typename T>
    class Vector
    {
    public:
        Vector(T x, T y, T z) : x_pos(x), y_pos(y), z_pos(z) {}
        Vector(T n) : x_pos(n), y_pos(n), z_pos(n) {}

        /*
    -- Getter Functions --
    */

        T get_x() const { return x_pos; }
        T get_y() const { return y_pos; }
        T get_z() const { return z_pos; }

        /*
-- Operator Overloading
    */
        //Scalar
        Vector<T> operator*(const T &d) const { return Vector<T>(x_pos * d, y_pos * d, z_pos * d); };
        //Multiplying Vectors
        Vector<T> operator*(const Vector<T> &v) const { return Vector<T>(x_pos * v.x_pos, y_pos * v.y_pos, z_pos * v.z_pos); };
        Vector<T> operator/(const T &d) const { return Vector<T>(x_pos / d, y_pos / d, z_pos / d); }
        Vector<T> operator+(const Vector<T> &v) const { return Vector<T>(x_pos + v.x_pos, y_pos + v.y_pos, z_pos + v.z_pos); }
        Vector<T> operator-(const Vector<T> &v) const { return Vector<T>(x_pos - v.x_pos, y_pos - v.y_pos, z_pos - v.z_pos); }
        //Formula
        T dot_product(Vector<T> a);
        Vector<T> cross_product(Vector<T> a);
        //2X2 Matrix
        T constexpr magnitude();
        Vector<T> &normalize();

    private:
        T x_pos,
            y_pos,
            z_pos;
    };
} // namespace raycast

//Typedef
typedef raycast::Vector<float> vecfloat;
typedef raycast::Vector<int> vecint;
typedef raycast::Vector<double> vecdouble;

#endif