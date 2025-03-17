#pragma once
#include "Ray.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Material.h"
#include "Object.h"

class Triangle : public Object{
    private:
        Vector3 v0;
        Vector3 v1;
        Vector3 v2;
        Vector2 vt0;
        Vector2 vt1;
        Vector2 vt2;
        Material material;
    public:

        /**
         * constructor for triangle
         * 
         * @param v0_ first vertex
         * @param v1_ second vertex
         * @param v2_ third vertex
         * @param material_ material for the triangle
         */
        Triangle(Vector3& v0_, Vector3& v1_, Vector3& v2_, Material& material_);

        /**
         * constructor for triangle with texture coordinates
         * 
         * @param v0_ first vertex
         * @param v1_ second vertex
         * @param v2_ third vertex
         * @param material_ material for the triangle
         * @param vt0_ first vertex texture coordinate
         * @param vt1_ second vertex texture coordinate
         * @param vt2_ third vertex texture coordinate
         */
        Triangle(Vector3& v0_, Vector3& v1_, Vector3& v2_, Material& material_, 
            Vector2& vt0_, Vector2& vt1_, Vector2& vt2_);
        const Vector3& getV0() const { return v0; }
        const Vector3& getV1() const { return v1; }
        const Vector3& getV2() const { return v2; }
        const Material& getMaterial() const override { return material; }
        const Vector2& getVt0() const { return vt0; }
        const Vector2& getVt1() const { return vt1; }
        const Vector2& getVt2() const { return vt2; }

        /**
         * Tests if a ray interesects a triangle and stores the minimum distance the intersection occured at.
         *
         * @param ray the ray to test for intersection
         * @param minT the minimum distance at which an intersection occurs
         * 
         * @return true if the ray interects the triangle
         */
        bool rayIntersects(const Ray& ray, float& minT) const override;

        /**
         * Tests if a triangle object is equivalent to another. Equivalent triangles have the same vertices
         * 
         * @param o the triangle to test equality against
         * 
         * @return true if o equals the triangle that calls this function, false otherwise
         */
        bool equals(const Object& o) const override;

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
         * Calculates the barycentric coordinates of the triangle
         * 
         * @param intersectionPoint the point used to calculate the normal
         * 
         * @return the barycentric coordinates stored in a vector3 where alpha = x, beta = y, gamma = z
         */
        Vector3 calculateBarycentricCoords(const Vector3& intersectionPoint) const;

        /**
         * prints information about the triangle
         */
        void printInfo() const override;
};