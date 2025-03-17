#pragma once
#include "Triangle.h"
#include "Vector3.h"

class SmoothShadedTriangle : public Triangle {
    private:
        Vector3 n0;
        Vector3 n1;
        Vector3 n2;
    public:
        SmoothShadedTriangle(Vector3& v0_, Vector3& v1_, Vector3& v2_, Material& material_,
            Vector3& n0_, Vector3& n1_, Vector3& n2_);
        SmoothShadedTriangle(Vector3& v0_, Vector3& v1_, Vector3& v2_, Material& material_, 
            Vector2& vt0_, Vector2& vt1_, Vector2& vt2_, Vector3& n0_, Vector3& n1_, Vector3& n2_);

        /**
         * Calculates the normal at a given point
         * 
         * @param intersectionPoint the point to calculate the normal at
         * 
         * @return the normal at the intersected point
         */
        Vector3 calculateNormal(const Vector3& intersectionPoint) const override;

        /**
         * prints information about the triangle
         * 
         */
        void printInfo() const override;
};