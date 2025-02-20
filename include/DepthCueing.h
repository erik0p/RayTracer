#pragma once
#include "Color.h"
#include <ostream>

class DepthCueing {
    private:
        Color depthColor;
        float aMin;
        float aMax;
        float distMin;
        float distMax;
    public:
        DepthCueing();
        DepthCueing(Color depthColor_, float aMin_, float aMax_, float distMin_, float distMax_);
        const Color& getDepthColor() const { return depthColor; }
        const float getAMin() const { return aMin; }
        const float getAMax() const { return aMax; }
        const float getDistMin() const { return distMin; }
        const float getDistMax() const { return distMax; }

        Color applyDepthCueing(const Color& color, float objDistance) const;

        friend std::ostream& operator<<(std::ostream& out, const DepthCueing& depthCueing);
};