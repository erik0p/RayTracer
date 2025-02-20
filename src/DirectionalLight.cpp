#include "DirectionalLight.h"
#include "Vector3.h"
#include <iostream>

DirectionalLight::DirectionalLight() : Light() {}
DirectionalLight::DirectionalLight(const Vector3& dir_, float intensity_) : Light(dir_, intensity_) {}

Vector3 DirectionalLight::getDirToSource(const Vector3& point) const {
    return -1.0f * this->getDirOrCenter();
}

void DirectionalLight::printInfo() const {
    std::cout << "light: " << " dir: " << this->getDirOrCenter() << " intensity: " << this->getIntensity() << std::endl; 
}