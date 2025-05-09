#include "PointLight.h"
#include <iostream>

PointLight::PointLight() : Light() {}
PointLight::PointLight(const Vector3& dir_, float intensity_) : Light(dir_, intensity_) {}

Vector3 PointLight::getDirToSource(const Vector3& point) const {
    return this->getDirOrPoint() - point;
}

void PointLight::printInfo() const {
    std::cout << "light: " << " dir: " << this->getDirOrPoint() << " intensity: " << this->getIntensity() << std::endl; 
}