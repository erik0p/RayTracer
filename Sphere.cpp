#include <ostream>
#include "Sphere.h"

Sphere::Sphere(Point3& center_, float radius_): center(center_), radius(radius_) {}

std::ostream& operator<<(std::ostream& out, const Sphere& sphere) {
    out <<"sphere: "
        << "center: " << sphere.center
        << " radius: " << sphere.radius;
    return out;
}
