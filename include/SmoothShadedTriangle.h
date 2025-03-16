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
        const Vector3 calculateNormal(const Vector3& intersectionPoint) const override;
        void printInfo() const override;
};