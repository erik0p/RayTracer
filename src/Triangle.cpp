#include "Triangle.h"
#include "Vector3.h"

Triangle::Triangle(Vector3& v0_, Vector3& v1_, Vector3& v2_, Material& material_) {
    v0 = v0_;
    v1 = v1_;
    v2 = v2_;
    material = material_;
}

bool Triangle::rayIntersects(const Ray& ray, float& minT) const {
    float x = ray.getOrigin().getX();
    float y = ray.getOrigin().getY();
    float z = ray.getOrigin().getZ();
    float dx = ray.getDir().getX();
    float dy = ray.getDir().getY();
    float dz = ray.getDir().getZ();
    Vector3 n = calculateNormal(Vector3()); 
    float A = n.getX();
    float B = n.getY();
    float C = n.getZ();
    float D = -(A * v0.getX() + B * v0.getY() + C * v0.getZ());
    float t;

    // determine if intersects plane 

    float denominator = (A * dx + B * dy + C * dz);

    // check if ray is parallel to plane
    if (denominator == 0) {
        return false;
    }

    float numerator = -(A * x + B * y + C * z + D);

    t = numerator / denominator;

    if (t < 0) {
        return false;
    }

    minT = t;

    Vector3 intersectionPoint = ray.getOrigin() + minT * ray.getDir();

    // determine if inside triangle using barycentric coords

    Vector3 e1 = v1 - v0;
    Vector3 e2 = v2 - v0;
    Vector3 ep = intersectionPoint - v0;
    float d11 = e1.dot(e1);
    float d22 = e2.dot(e2);
    float d12 = e1.dot(e2);
    float d1p = e1.dot(ep);
    float d2p = e2.dot(ep);

    float determinant = d11 * d22 - d12 * d12;

    if (determinant == 0) {
        return false;
    }

    float beta = (d22 * d1p - d12 * d2p) / determinant;
    float gamma = (d11 * d2p - d12 * d1p) / determinant;
    float alpha = 1 - (beta + gamma);

    // point is outside
    if (alpha < 0 || beta < 0 || gamma < 0) {
        return false;
    }

    if (alpha + beta + gamma > 1) {
        return false;
    }


    return true;
}

bool Triangle::equals(const Object& o) const {
    const Triangle* t = dynamic_cast<const Triangle*>(&o);
    if (t) {
        return v0.equals(t->v0) && v1.equals(t->v1) && v2.equals(t->v2);
    }
    return false;
}

const Vector3 Triangle::calculateNormal(const Vector3& intersectionPoint) const {
    Vector3 e1 = v1 - v0;
    Vector3 e2 = v2 - v0;
    Vector3 N = Vector3::cross(e1, e2);
    N.normalize();
    return N;
}

const Vector3 Triangle::calculateBarycentricCoords(const Vector3& intersectionPoint) const {
    Vector3 e1 = v1 - v0;
    Vector3 e2 = v2 - v0;
    Vector3 ep = intersectionPoint - v0;
    float d11 = e1.dot(e1);
    float d22 = e2.dot(e2);
    float d12 = e1.dot(e2);
    float d1p = e1.dot(ep);
    float d2p = e2.dot(ep);

    float determinant = d11 * d22 - d12 * d12;

    float beta = (d22 * d1p - d12 * d2p) / determinant;
    float gamma = (d11 * d2p - d12 * d1p) / determinant;
    float alpha = 1 - (beta + gamma);

    return Vector3(alpha, beta, gamma);
}

void Triangle::printInfo() const {
    std::cout << "triangle: "
    << "v0: " << v0
    << " v1: " << v1
    << " v2: " << v2 << std::endl
    << "material: " << material << std::endl;
}