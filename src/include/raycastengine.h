#ifndef RAYCASTENGINE_H
#define RAYCASTENGINE_H
#include <iostream>
#include <cmath>
#include <vector>
//*Raytracer I named it wrong sorry
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

        Vector<T> operator*(const T &d) const { return Vector<T>(x_pos * d, y_pos * d, z_pos * d); }

        Vector<T> operator*(const Vector<T> &v) const { return Vector<T>(x_pos * v.x_pos, y_pos * v.y_pos, z_pos * v.z_pos); }
        Vector<T> operator/(const T &d) const { return Vector<T>(x_pos / d, y_pos / d, z_pos / d); }
        Vector<T> operator+(const Vector<T> &v) const { return Vector<T>(x_pos + v.x_pos, y_pos + v.y_pos, z_pos + v.z_pos); }
        Vector<T> operator-(const Vector<T> &v) const { return Vector<T>(x_pos - v.x_pos, y_pos - v.y_pos, z_pos - v.z_pos); }
        friend inline std::ostream &operator<<(std::ostream &os, Vector<T> a)
        {
            os << a.x_pos << " " << a.y_pos << " " << a.z_pos << std::endl;
            return os;
        }
        friend inline std::istream &operator>>(std::istream &is, Vector<T> a)
        {
            is >> a.x_pos >> a.y_pos >> a.z_pos;
            return is;
        }
        Vector<T> operator+=(const Vector<T> &v)
        {
            *this = v.normalize();
            return (*this);
        }
        /*
----------- FORMULAS ----------------------------

        */
        T dot_product(Vector<T> a)
        {
            return x_pos * a.x_pos + y_pos * a.y_pos + z_pos * a.z_pos;
        }
        Vector<T> cross_product(Vector<T> a) { return Vector<T>((get_y() * a.get_z() - get_z() * a.get_y()), (get_z * a.get_x - get_x * a.get_z), (get_x * a.get_y - get_y * a.get_x)); }
        //2X2 Matrix
        T magnitude() const
        {
            return sqrt(x_pos * x_pos + y_pos * y_pos + z_pos * z_pos);
        }
        Vector<T> &normalize()
        {
            T inverse = 1 / magnitude();
            x_pos *= inverse;
            y_pos *= inverse;
            z_pos *= inverse;
            return *this;
        }
        inline Vector<T> unit_vector()
        {
            T d = this->magnitude();
            return *this / d;
        }

    private:
           T x_pos,
            y_pos,
            z_pos;
    };
} // namespace raycast

//Typedefs
typedef raycast::Vector<float> vecfloat;
typedef raycast::Vector<int> vecint;
typedef raycast::Vector<double> vecdouble;

#endif
