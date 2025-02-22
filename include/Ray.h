#pragma once
#include "Vector3.h"

class Ray {
    private:
        Vector3 origin;
        Vector3 dir;
    public:
        Ray();

        /**
         * Constructor for a ray
         *
         * @param origin_ the origin point of the ray
         * @param dir_ the direction of the ray
         */
        Ray(const Vector3& origin_, const Vector3& dir_);

        const Vector3& getOrigin() const { return origin; }
        const Vector3& getDir() const { return dir; }

        /**
         * Overload the out stream operator to print a ray
         *
         * @param out the outstream
         * @param ray the ray whose fields are printed
         */
        friend std::ostream& operator<<(std::ostream& out, const Ray& ray);
};
