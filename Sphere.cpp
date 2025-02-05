#include <ostream>
#include "Sphere.h"
#include "Vector3.h"
#include "Color.h"

Sphere::Sphere(Vector3& center_, float radius_, Color& color_) {
    center = center_;
    radius = radius_;
    color = color_;
}

std::ostream& operator<<(std::ostream& out, const Sphere& sphere) {
    out <<"sphere: "
        << "center: " << sphere.center
        << " radius: " << sphere.radius
        << " color: " << sphere.color;
    return out;
}
