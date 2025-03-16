#include <ostream>
#include <cmath>
#include "Sphere.h"
#include "Vector3.h"
#include "Material.h"
#include "Object.h"

Sphere::Sphere(Vector3& center_, float radius_, Material& material_) {
    center = center_;
    radius = radius_;
    material = material_;
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
    float b = 2.0f * (dx * (x - cx) + dy * (y - cy) + dz * (z - cz));
    float c = pow(x - cx, 2) + pow(y - cy, 2) + pow(z - cz, 2) - pow(r, 2);
    float discriminant = pow(b, 2) - 4.0f * a * c;

    
    if (discriminant < 0.0f) { // No intersection
        return false;
    }

    bool intersectionFound = false;

    if (discriminant > 0.0f) { // pierces sphere
        float t1 = (-b + sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b - sqrt(discriminant)) / (2.0f * a);
        // std::cout << "t1: " << t1 << ", t2: " << t2 << std::endl;
        if (t1 < minT && t1 > 0.0f) {
            minT = t1;
            intersectionFound = true;
        }
        if (t2 < minT && t2 > 0.0f) {
            minT = t2;
            intersectionFound = true;
        }
    } else if (discriminant == 0.0f) { // grazes sphere
        float t = -b / (2.0f * a);
        if (t < minT && t > 0.0f)
        {
            minT = t;
            intersectionFound = true;
        }
    }
    if (!intersectionFound) {
        return false;
    }
    return true;
}

bool Sphere::equals(const Object& o) const {
    const Sphere* s = dynamic_cast<const Sphere*>(&o);
    if (s) {
        return center.equals(s->center) && radius == s->radius;
    }
    return false;
}

const Vector3 Sphere::calculateNormal(const Vector3& intersectionPoint) const {
    Vector3 N = (intersectionPoint - center) / radius;
    N.normalize();
    return N;
}


void Sphere::printInfo() const {
    std::cout <<"sphere: "
        << "center: " << center
        << " radius: " << radius << std::endl
        << "material: " << material << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Sphere& sphere) {
    out <<"sphere: "
        << "center: " << sphere.center
        << " radius: " << sphere.radius << std::endl
        << "material: " << sphere.material;
    return out;
}
