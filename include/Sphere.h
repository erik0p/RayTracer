#pragma once
#include "Vector3.h"
#include "Material.h"
#include "Object.h"
#include "Ray.h"

class Sphere : public Object {
    private:
        Vector3 center;
        float radius;
        Material material;
    public:

        /**
         * Constructor for a sphere
         *
         * @param center_ the center point of the sphere
         * @param radius_ radius of the sphere
         * @param color_ the color the sphere has
         */
        Sphere(Vector3& center_, float radius_, Material& material_);
        ~Sphere();

        const Vector3& getCenter() const { return center; }
        float getRadius() const { return radius; }
        const Material& getMaterial() const override { return material; }

        /**
         * Tests if a ray interesects a sphere and stores the minimum distance the intersection occured at.
         *
         * @param ray the ray to test for intersection
         * @param minT the minimum distance at which an intersection occurs
         * 
         * @return true if the ray interects the sphere
         */
        bool rayIntersects(const Ray& ray, float& minT, float& maxT) const override;

        /**
         * Calculates the normal at a given point
         * 
         * @param intersectionPoint the point to calculate the normal at
         * 
         * @return the normal at the intersected point
         */
        Vector3 calculateNormal(const Vector3& intersectionPoint) const override;

        /**
         * Calculates the color at a given point
         * 
         * @param intersectionPoint the point to calculate the color at
         * 
         * @return the color at the intersected point
         */
        Color calculateColor(const Vector3& intersectionPoint) const override;

        /**
         * Tests if a sphere object is equivalent to another. Equivalent spheres have the same radius and center
         * 
         * @param s the sphere to test equality against
         * 
         * @return true if s equals the sphere that calls this function, false otherwise
         */
        bool equals(const Object& o) const override;

        /**
         * print information about the sphere
         *
         */
        void printInfo() const override;


        /**
         * Overload the out stream operator to print a sphere
         *
         * @param out the outstream
         * @param sphere the sphere whose fields are printed
         */
        friend std::ostream& operator<<(std::ostream& out, const Sphere& sphere);
};
