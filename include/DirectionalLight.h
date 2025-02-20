#pragma once
#include "Light.h"
#include "Vector3.h"

class DirectionalLight : public Light {
    public:
        DirectionalLight();
        DirectionalLight(const Vector3 &dir_, float intensity_);
        Vector3 getDirToSource(const Vector3 &point) const override;
        void printInfo() const override;
};