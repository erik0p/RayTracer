#include <ostream>
#include <cmath>
#include "Sphere.h"
#include "Vector3.h"
#include "Color.h"
#include "Object.h"

Sphere::Sphere(Vector3& center_, float radius_, Color& color_) {
    center = center_;
    radius = radius_;
    color = color_;
}

Sphere::~Sphere() {}

bool Sphere::rayIntersects(const Ray& ray, float& minT) const {
    float x = ray.getOrigin().getX();
    float y = ray.getOrigin().getY();
    float z = ray.getOrigin().getZ();
    float dx = ray.getDir().getX();
    float dy = ray.getDir().getY();
    float dz = ray.getDir().getZ();
    float cx = this->getCenter().getX();
    float cy = this->getCenter().getY();
    float cz = this->getCenter().getZ();
    float r = this->getRadius();

    float a = 1.0f;
    // float a = pow(dx, 2) + pow(dy, 2) + pow(dz, 2);
    float b = 2.0f * (dx * (x - cx) + dy * (y - cy) + dz * (z - cz));
    float c = pow(x - cx, 2) + pow(y - cy, 2) + pow(z - cz, 2) - pow(r, 2);
    float discriminant = pow(b, 2) - 4.0f * a * c;

    if (discriminant > 0.0f) { // pierces sphere
        float t1 = (-b + sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b - sqrt(discriminant)) / (2.0f * a);
        if (t1 < minT && t1 > 0.0f) {
            minT = t1;
        }
        if (t2 < minT && t2 > 0.0f) {
            minT = t2;
        }
        return true;
    } else if (discriminant == 0.0f) { // grazes sphere
        float t = -b / (2.0f * a);
        if (t < minT && t > 0.0f)
        {
            minT = t;
        }
        return true;
    }
    return false;
}

void Sphere::print(std::ostream& out) const {
    out <<"sphere: "
        << "center: " << center
        << " radius: " << radius
        << " color: " << color;
}

// std::ostream& operator<<(std::ostream& out, const Sphere& sphere) {
//     out <<"sphere: "
//         << "center: " << sphere.center
//         << " radius: " << sphere.radius
//         << " color: " << sphere.color;
//     return out;
// }
