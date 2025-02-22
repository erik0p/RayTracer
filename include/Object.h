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

        /**
         * Tests if a ray interesects a object and stores the minimum distance the intersection occured at.
         *
         * @param ray the ray to test for intersection
         * @param minT the minimum distance at which an intersection occurs
         * 
         * @return true if the ray interects the object
         */
        virtual bool rayIntersects(const Ray& ray, float& minT, Vector3* intersectionPoint) const = 0;
        virtual const Material& getMaterial() const = 0;

        /**
         * prints information about the object
         */
        virtual void print(std::ostream& out) const = 0;
};
