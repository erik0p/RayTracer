#include <ostream>
#include <cmath>
#include "Sphere.h"
#include "Utils.h"
#include "Vector3.h"
#include "Material.h"
#include "Object.h"

Sphere::Sphere(Vector3& center_, float radius_, Material* material_) {
    center = center_;
    radius = radius_;
    material = material_;
}

Sphere::~Sphere() {
}

bool Sphere::rayIntersects(const Ray& ray, float& minT, float& maxT) const {
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
            maxT = t2;
            intersectionFound = true;
        }
        if (t2 < minT && t2 > 0.0f) {
            minT = t2;
            maxT = t1;
            intersectionFound = true;
        }
    } else if (discriminant == 0.0f) { // grazes sphere
        float t = -b / (2.0f * a);
        if (t < minT && t > 0.0f)
        {
            minT = t;
            maxT = t;
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

Vector3 Sphere::calculateNormal(const Vector3& intersectionPoint) const {
    Vector3 N = (intersectionPoint - center) / radius;
    N.normalize();
    return N;
}

Color Sphere::calculateColor(const Vector3& intersectionPoint) const {
    if (!material->getTextureFlag()) {
        return material->getDiffuseColor();
    } else {
        Vector3 normal = calculateNormal(intersectionPoint);
        float phi = acos(normal.getZ());
        float theta = atan2(normal.getY(), normal.getX());
        if (theta < 0.0f) {
            theta += 2.0f * utils::PI;
        }
        double v = phi / utils::PI;
        double u = theta / (2.0f * utils::PI);
        double x;

        if (u > 1.0f) {
            u = modf(u, &x);
        }
        if (v > 1.0f) {
            v = modf(v, &x);
        }

        int j = round(u * (material->getTextureWidth() - 1));
        int i = round(v * (material->getTextureHeight() - 1));
        Color color = material->lookupColor(i, j);
        return color;
    }
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
