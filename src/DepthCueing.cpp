#include "DepthCueing.h"
#include "Color.h"
#include <ostream>

DepthCueing::DepthCueing() {
    depthColor = Color();
    aMin = 0.0f;
    aMax = 0.0f;
    distMin = 0.0f;
    distMax = 0.0f;
}

DepthCueing::DepthCueing(Color depthColor_, float aMin_, float aMax_, float distMin_, float distMax_) {
    depthColor = depthColor_;
    aMin = aMin_;
    aMax = aMax_;
    distMin = distMin_;
    distMax = distMax_;
}

Color DepthCueing::applyDepthCueing(const Color& color, float objDistance) const {
    float adc = 0.0f;
    Color result;
    
    if (objDistance < distMin) {
        adc = aMax;
    } else if (distMin <= objDistance && objDistance <= distMax) {
        adc = aMin + (aMax - aMin) * ((distMax - objDistance) / (distMax - distMin));
    } else if (objDistance >= distMax) {
        adc = aMin;
    }

    result = adc * color + (1.0f - adc) * depthColor;

    return result;
}

std::ostream &operator<<(std::ostream& out, const DepthCueing& depthCueing) {
    out << "depthcueing: " << depthCueing.depthColor << " aMin: " << depthCueing.aMin
    << " aMax: " << depthCueing.aMax << " distMin: " << depthCueing.distMin
    << " distMax: " << depthCueing.distMax;
    return out;
}