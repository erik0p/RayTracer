#pragma once
#include "Light.h"
#include "Vector3.h"

class PointLight : public Light {
    public:
        PointLight();
        PointLight(const Vector3& dir_, float intensity_);
        Vector3 getDirToSource(const Vector3 &point) const override;
        void printInfo() const override;
};