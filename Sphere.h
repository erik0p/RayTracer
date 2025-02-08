#pragma once
#include "Vector3.h"
#include "Object.h"
#include "Color.h"

class Sphere : public Object {
    private:
        Vector3 center;
        float radius;
        Color color;
    public:
        Sphere(Vector3& center_, float radius_, Color& color_);
        ~Sphere() override;

        const Vector3& getCenter() const { return center; }
        float getRadius() const { return radius; }
        const Color& getColor() const { return color; } 
        bool rayIntersects(const Ray& ray, float& minT) const override;
        void print(std::ostream& out) const;
        // friend std::ostream& operator<<(std::ostream& out, const Sphere& sphere);
};
