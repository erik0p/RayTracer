#pragma once
#include "Ray.h"
#include "Material.h"
#include "Vector3.h"

class Object {
    private:
        Material material;
    public:
        Object();
        virtual ~Object();
        virtual bool rayIntersects(const Ray& ray, float& minT, Vector3* intersectionPoint) const = 0;
        virtual const Material& getMaterial() const = 0;
        virtual void print(std::ostream& out) const = 0;
};
