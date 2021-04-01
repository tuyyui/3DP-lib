#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable
{
public:
    sphere() {}
    ~sphere() {std::cout << "Destroying" << std::endl;};
    sphere(vecfloat cen, float r) : center(cen), radius(r) {}
    bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const
    {
        vecfloat oc = r.origin() - center;
        vecfloat getr = r.direction();
        float a = getr.dot_product(r.direction());
        float b = oc.dot_product(r.direction());
        float c = oc.dot_product(oc) - (radius * radius);
        float discriminant = b * b - a * c;
        if (discriminant > 0)
        {
            float temp = (-b - sqrt(b * b - a * c)) / a;
            if (temp < t_max && temp > t_min)
            {
                rec.t = temp;
                rec.p = r.point_at_parameter(rec.t);
                rec.normal = (rec.p - center) / radius;
                return true;
            }
            temp = (-b + sqrt(b * b - a * c)) / a;
            if (temp < t_max && temp > t_min)
            {
                rec.t = temp;
                rec.p = r.point_at_parameter(rec.t);
                rec.normal = (rec.p - center) / radius;
                return true;
            }
        }
        return false;
    }

protected:
    vecfloat center;
    float radius;
};

#endif
