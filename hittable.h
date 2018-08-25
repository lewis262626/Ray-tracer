#ifndef HITTABLEH
#define HITTABLEH

#include "ray.h"

struct hit_records {
    float t;
    vec3 p;
    vec3 normal;
};

class hittable {
    public:
        virtual bool hit(const ray &r, float t_min, float t_max, hit_records &rec) const = 0;
};

#endif
