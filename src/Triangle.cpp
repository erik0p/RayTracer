#include "Triangle.h"
#include "Vector3.h"
#include <cmath>
#include <algorithm>

Triangle::Triangle(Vector3& v0_, Vector3& v1_, Vector3& v2_, Material& material_) {
    v0 = v0_;
    v1 = v1_;
    v2 = v2_;
    material = material_;
}

Triangle::Triangle(Vector3& v0_, Vector3& v1_, Vector3& v2_, Material& material_, 
    Vector2& vt0_, Vector2& vt1_, Vector2& vt2_) {
    v0 = v0_;
    v1 = v1_;
    v2 = v2_;
    vt0 = vt0_;
    vt1 = vt1_;
    vt2 = vt2_;
    material = material_;
}

bool Triangle::rayIntersects(const Ray& ray, float& minT) const {
    float x = ray.getOrigin().getX();
    float y = ray.getOrigin().getY();
    float z = ray.getOrigin().getZ();
    float dx = ray.getDir().getX();
    float dy = ray.getDir().getY();
    float dz = ray.getDir().getZ();

    Vector3 e1 = v1 - v0;
    Vector3 e2 = v2 - v0;
    Vector3 n = Vector3::cross(e1, e2);
    n.normalize();

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

    // distance where intersection occurs
    t = numerator / denominator;

    // intersection is behind ray origin
    if (t < 0) { 
        return false;
    }

    minT = t;

    Vector3 intersectionPoint = ray.getOrigin() + t * ray.getDir();

    // determine if inside triangle using barycentric coords
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

    // point is outside
    if (alpha > 1 || beta > 1 || gamma > 1) {
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

Vector3 Triangle::calculateNormal(const Vector3& intersectionPoint) const {
    Vector3 e1 = v1 - v0;
    Vector3 e2 = v2 - v0;
    Vector3 N = Vector3::cross(e1, e2);
    N.normalize();
    return N;
}

Color Triangle::calculateColor(const Vector3& intersectionPoint) const {
    if (!material.getTextureFlag()) {
        return material.getDiffuseColor();
    } else {
        Vector3 barycentricCoords = calculateBarycentricCoords(intersectionPoint);
        float alpha = barycentricCoords.getX();
        float beta = barycentricCoords.getY();
        float gamma = barycentricCoords.getZ();

        double u = alpha * vt0.getX() + beta * vt1.getX() + gamma * vt2.getX();
        double v = alpha * vt0.getY() + beta * vt1.getY() + gamma * vt2.getY();

        double x;
        if (u > 1.0) {
            u = modf(u, &x);
        }
        if (v > 1.0) {
            v = modf(v, &x);
        }

        int j = round(u * (material.getTextureWidth() - 1));
        int i = round(v * (material.getTextureHeight() - 1));

        Color color = material.lookupColor(i, j);
        return color;
    }
}

Vector3 Triangle::calculateBarycentricCoords(const Vector3& intersectionPoint) const {
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
    float alpha = 1.0f - (beta + gamma);

    return Vector3(alpha, beta, gamma);
}

void Triangle::printInfo() const {
    std::cout << "triangle: "
    << "v0: " << v0
    << " v1: " << v1
    << " v2: " << v2 << std::endl
    << "material: " << material << std::endl;
}