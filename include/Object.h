#pragma once
#include "Ray.h"
#include "Color.h"

class Object {
    private:
        Color color;
    public:
        Object();
        virtual ~Object();
        virtual bool rayIntersects(const Ray& ray, float& minT) const = 0;
        virtual const Color& getColor() const = 0;
        virtual void print(std::ostream& out) const = 0;
};
