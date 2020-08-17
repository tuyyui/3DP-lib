#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable
{
public:
    //sphere(){};
    sphere(vecfloat cen, float r) : center(cen), radius(r) {}
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec);

protected:
    vecfloat center;
    float radius;
};

#endif