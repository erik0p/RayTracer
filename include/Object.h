#pragma once
#include "Ray.h"
#include "Material.h"
#include "Vector3.h"

class Object {
    private:
        Material* material;
    public:
        Object();
        virtual ~Object();

        /**
         * Tests if a ray interesects a object and stores the minimum distance the intersection occured at and the further distance along the path of the ray.
         *
         * @param ray the ray to test for intersection
         * @param minT the minimum distance at which an intersection occurs
         * @param maxT the further distance of t along the path which the nearest intersection occured at
         * 
         * @return true if the ray interects the object
         */
        virtual bool rayIntersects(const Ray& ray, float& minT, float& maxT) const = 0;
        virtual bool equals(const Object& o) const = 0;
        virtual const Material* getMaterial() const = 0;
        virtual Vector3 calculateNormal(const Vector3& intersectionPoint) const = 0;
        virtual Color calculateColor(const Vector3& intersectionPoint) const = 0;

        /**
         * prints information about the object
         */
        virtual void printInfo() const = 0;
};
