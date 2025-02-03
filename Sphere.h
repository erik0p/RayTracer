#pragma once
#include "Point3.h"

class Sphere {
    private:
        Point3 center;
        float radius;
    public:
        Sphere(Point3& center_, float radius_);

        const Point3& getCenter() const { return center; }
        float getRadius() const { return radius; }
        friend std::ostream& operator<<(std::ostream& out, const Sphere& sphere);
};
