#pragma once
#include "Vector3.h"
#include <ostream>

class Light {

    public:
        Vector3 dir;
        float intensity;
        Light();
        virtual ~Light();
        Light(const Vector3& dir_, float intensity_);
        const Vector3& getDir() const { return dir; }
        const float getIntensity() const { return intensity; }
        virtual Vector3 getDirToSource(const Vector3& point) const = 0;
        virtual void printInfo() const = 0;

        friend std::ostream& operator<<(std::ostream& out, const Light& light);
};