#include "include/raycastengine.h"

template <typename T>
T raycast::Vector<T>::dot_product(Vector<T> a)
{
    return get_x() * a.get_x() + get_y * a.get_y + get_z * a.get_z;
}

template <typename T>
raycast::Vector<T> raycast::Vector<T>::cross_product(Vector<T> a)
{
    return Vector<T>((get_y() * a.get_z() - get_z() * a.get_y()), (get_z * a.get_x - get_x * a.get_z), (get_x * a.get_y - get_y * a.get_x));
}

template <typename T>
T constexpr raycast::Vector<T>::magnitude()
{
    return sqrt(get_x * get_x + get_y * get_y + get_z * get_z);
}

template <typename T>

raycast::Vector<T> &raycast::Vector<T>::normalize()
{
    T inverse = 1 / magnitude();
    x_pos *= inverse;
    y_pos *= inverse;
    z_pos *= inverse;
    return *this;
}
