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

        /**
         * constructor for depthcueing
         *
         * @param depthColor_ color to use for depth cueing
         * @param aMin_ the minimum scalar for depth cueing
         * @param aMax_ the maximum scalar for depth cueing
         * @param distMin_ the minimum distance for depth cueing
         * @param distMax the maximum distance for depth cueing
         *
         */
        DepthCueing(Color depthColor_, float aMin_, float aMax_, float distMin_, float distMax_);
        const Color& getDepthColor() const { return depthColor; }
        const float getAMin() const { return aMin; }
        const float getAMax() const { return aMax; }
        const float getDistMin() const { return distMin; }
        const float getDistMax() const { return distMax; }

        /**
         * blends a color with the depth cue color based on an objects distance from the eye
         *
         * @param color the illumination to apply depth cueing to
         * @param objDistance the distance of the object from the eye
         *
         * @return the color resulting from blending with the depth cue color
         */
        Color applyDepthCueing(const Color& color, float objDistance) const;

        /**
         * Overload the out stream operator to print depthcueing info
         *
         * @param out the outstream
         * @param depthCueing the depthCueing object whose fields are printed
         */
        friend std::ostream& operator<<(std::ostream& out, const DepthCueing& depthCueing);
};