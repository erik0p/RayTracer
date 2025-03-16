#pragma once
#include "Ray.h"
#include "Vector3.h"
#include "Material.h"
#include "Object.h"

class Triangle : public Object{
    private:
        Vector3 v0;
        Vector3 v1;
        Vector3 v2;
        Vector3 normal;
        Material material;
    public:
        Triangle(Vector3& v0_, Vector3& v1_, Vector3& v2_, Material& material_);
        const Vector3& getV0() const { return v0; }
        const Vector3& getV1() const { return v1; }
        const Vector3& getV2() const { return v2; }
        const Material& getMaterial() const override { return material; }
        bool rayIntersects(const Ray& ray, float& minT) const override;
        bool equals(const Object& o) const override;
        const Vector3 calculateNormal(const Vector3& intersectionPoint) const override;
        const Vector3 calculateBarycentricCoords(const Vector3& intersectionPoint) const;
        void printInfo() const override;
};