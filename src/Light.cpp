#include "Light.h"
#include "Vector3.h"
#include <ostream>

Light::~Light() {}

Light::Light() {
    dir = Vector3();
}

Light::Light(const Vector3& dir_, int type_, float intensity_) {
    dir = dir_;
    type = type_;
    intensity = intensity_;
}

bool Light::isDirectionalLight() const {
    return type == 0;
}

std::ostream& operator<<(std::ostream& out, const Light& light) {
    out << "light: " << "dir: " << light.dir << " type: " << light.type
    << " intensity: " << light.intensity; 
    return out;
}