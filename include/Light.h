#pragma once
#include "Vector3.h"
#include <ostream>

class Light {

    public:
        Vector3 dir;
        float intensity;
        Light();
        virtual ~Light();

        /**
         * constructor for attenuationlight 
         * 
         * @param dir_ the position of the light
         * @param intensity_ the intensity of the light
         */
        Light(const Vector3& dir_, float intensity_);
        const Vector3& getDirOrPoint() const { return dir; }
        const float getIntensity() const { return intensity; }

        /**
         * calculates the direction to this light
         * 
         * @param point the intersection point of the surface
         * 
         * @return the direction to this light
         */
        virtual Vector3 getDirToSource(const Vector3& point) const = 0;

        /**
         * prints information about the light
         */
        virtual void printInfo() const = 0;

        /**
         * Overload the out stream operator to print depthcueing info
         *
         * @param out the outstream
         * @param light the light object whose fields are printed
         */
        friend std::ostream& operator<<(std::ostream& out, const Light& light);
};