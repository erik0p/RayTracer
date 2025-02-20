#pragma once
#include "Light.h"

class AttenuationLight : public Light {
    public:
        float c1;
        float c2;
        float c3;
        AttenuationLight();
        AttenuationLight(const Vector3 &dir_, float intensity_, float c1_, float c2_, float c3_);
        float attenuation(float distance) const;
        Vector3 getDirToSource(const Vector3 &point) const override;
        void printInfo() const override;
};