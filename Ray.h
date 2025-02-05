#pragma once
#include "Vector3.h"

class Ray {
    private:
        Vector3 origin;
        Vector3 dir;
    public:
        Ray();
        Ray(Vector3& origin_, Vector3& dir_);
        const Vector3& getOrigin() const { return origin; }
        const Vector3& getDir() const { return dir; }
        friend std::ostream& operator<<(std::ostream& out, const Ray& ray);
};
