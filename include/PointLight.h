#pragma once
#include "Light.h"
#include "Vector3.h"

class PointLight : public Light {
    public:
        PointLight();

        /**
         * constructor for pointlight 
         * 
         * @param dir_ the position of the light
         * @param intensity_ the intensity of the light
         */
        PointLight(const Vector3& dir_, float intensity_);

        /**
         * calculates the direction to this light
         * 
         * @param point the intersection point of the surface
         * 
         * @return the direction to this light
         */
        Vector3 getDirToSource(const Vector3 &point) const override;

        /**
         * prints information about the light
         */
        void printInfo() const override;
};