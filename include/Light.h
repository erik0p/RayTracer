#pragma once
#include "Vector3.h"
#include <ostream>

class Light {
    private:
        Vector3 dir;
        int type;
        float intensity;

    public:
        Light();
        ~Light();
        Light(const Vector3& dir_, int type_, float intensity_);
        const Vector3& getDir() const { return dir; }
        const int getType() const { return type; }
        const float getIntensity() const { return intensity; }
        bool isDirectionalLight() const;

        friend std::ostream& operator<<(std::ostream& out, const Light& light);
};