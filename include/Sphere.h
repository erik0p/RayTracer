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

        /*
         * Constructor for a sphere
         *
         * @param center_ the center point of the sphere
         * @param radius_ radius of the sphere
         * @param color_ the color the sphere has
         */
        Sphere(Vector3& center_, float radius_, Color& color_);
        ~Sphere() override;

        const Vector3& getCenter() const { return center; }
        float getRadius() const { return radius; }
        const Color& getColor() const { return color; } 

        /*
         * Tests if a ray interesects a sphere and stores the minimum distance the intersection occured at.
         *
         * @param ray the ray to test for intersection
         * @param minT the minimum distance at which an intersection occurs
         * 
         * @return true if the ray interects the sphere
         */
        bool rayIntersects(const Ray& ray, float& minT) const override;

        /*
         * Appends to the outstream
         *
         * @param out the outstream
         */
        void print(std::ostream& out) const;


        /*
         * Overload the out stream operator to print a sphere
         *
         * @param out the outstream
         * @param sphere the sphere whose fields are printed
         */
        friend std::ostream& operator<<(std::ostream& out, const Sphere& sphere);
};
