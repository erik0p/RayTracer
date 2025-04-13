#pragma once
#include "Light.h"

class AttenuationLight : public Light {
    public:
        float c1;
        float c2;
        float c3;

        AttenuationLight();

        /**
         * constructor for attenuationlight 
         * 
         * @param dir_ the position of the light
         * @param intensity_ the intensity of the light
         * @param c1_ scalar for attenuation factor
         * @param c2_ scalar for attenuation factor
         * @param c3_ scalar for attenuation factor
         */
        AttenuationLight(const Vector3 &dir_, float intensity_, float c1_, float c2_, float c3_);

        /**
         * calculates the attenuation factor for the light
         * 
         * @param distance distance from intersection point to the light source
         * 
         * @return the attenuation factor
         */
        float attenuation(float distance) const;

        /**
         * calculates the direction to this light
         * 
         * @param point the intersection point of the surface
         * 
         * @return the direction to this light
         */
        Vector3 getDirToSource(const Vector3& point) const override;

        /**
         * prints information about the light
         */
        void printInfo() const override;
};