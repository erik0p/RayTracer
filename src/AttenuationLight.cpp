#include "AttenuationLight.h"
#include <iostream>
#include <cmath>

AttenuationLight::AttenuationLight() : Light() {}
AttenuationLight::AttenuationLight(const Vector3& dir_, float intensity_, float c1_, float c2_, float c3_) : Light(dir_, intensity_) {
    c1 = c1_;
    c2 = c2_;
    c3 = c3_;
}

Vector3 AttenuationLight::getDirToSource(const Vector3& point) const {
    return this->getDirOrCenter() - point;
}

float AttenuationLight::attenuation(float distance) const {
    return (1.0f / (c1 + c2 * distance + c3 * pow(distance, 2.0f)));
}

void AttenuationLight::printInfo() const {
    std::cout << "light: " << " dir: " << this->getDirOrCenter() << " intensity: " << this->getIntensity()
    << " c1: " << c1 << " c2: " << c2 << " c3: " << c3 << std::endl;; 
}