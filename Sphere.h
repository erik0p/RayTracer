#pragma once
#include "Vector3.h"
#include "Color.h"

class Sphere {
    private:
        Vector3 center;
        float radius;
        Color color;
    public:
        Sphere(Vector3& center_, float radius_, Color& color_);

        const Vector3& getCenter() const { return center; }
        float getRadius() const { return radius; }
        const Color& getColor() const { return color; } 
        friend std::ostream& operator<<(std::ostream& out, const Sphere& sphere);
};
