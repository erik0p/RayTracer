#include "Light.h"
#include "Vector3.h"
#include <ostream>

Light::~Light() {}

Light::Light() {
    dir = Vector3();
}

Light::Light(const Vector3& dir_, float intensity_) {
    dir = dir_;
    intensity = intensity_;
}


std::ostream& operator<<(std::ostream& out, const Light& light) {
    out << "light: " << "dir: " << light.dir
    << " intensity: " << light.intensity; 
    return out;
}