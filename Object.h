#pragma once
#include "Ray.h"

class Object {
    public:
        Object();
        bool intersects(const Ray& ray) const;
};
