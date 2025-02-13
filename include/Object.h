#pragma once
#include "Ray.h"
#include "Color.h"

class Object {
    private:
        Color color;
    public:
        Object();
        virtual ~Object();

        /*
         * Constructor for color.
         *
         * @param ray the ray to test for intersection
         * @param minT the minimum distance at which an intersection occurs
         * 
         * return true if the ray interects the sphere
         */
        virtual bool rayIntersects(const Ray& ray, float& minT) const = 0;
        virtual const Color& getColor() const = 0;
        virtual void print(std::ostream& out) const = 0;
};
