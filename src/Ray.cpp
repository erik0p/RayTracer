#include <ostream>
#include "Ray.h"
#include "Vector3.h"

Ray::Ray() {
    origin = Vector3::ZERO;
    dir = Vector3::UP;
}

Ray::Ray(const Vector3& origin_, const Vector3& dir_) {
    origin = origin_;
    dir = dir_;
}

std::ostream& operator<<(std::ostream& out, const Ray& ray) {
    out <<"ray: " << "origin: " << ray.origin << "dir: " << ray.dir;
    return out;
}
