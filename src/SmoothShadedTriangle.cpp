#include "Triangle.h"
#include "SmoothShadedTriangle.h"

SmoothShadedTriangle::SmoothShadedTriangle(Vector3 &v0_, Vector3 &v1_, Vector3 &v2_, Material &material_,
                                           Vector3 &n0_, Vector3 &n1_, Vector3 &n2_) : Triangle(v0_, v1_, v2_, material_) {
    n0 = n0_;
    n1 = n1_;
    n2 = n2_;
}
const Vector3 SmoothShadedTriangle::calculateNormal(const Vector3& intersectionPoint) const {
    Vector3 barycentricCoords = calculateBarycentricCoords(intersectionPoint);
    float alpha = barycentricCoords.getX();
    float beta = barycentricCoords.getY();
    float gamma = barycentricCoords.getZ();
    Vector3 N = (alpha * n0 + beta * n1 + gamma * n2); 
    N.normalize();
    return N;
}

void SmoothShadedTriangle::printInfo() const { 
    std::cout << "smooth shaded triangle: "
    << "v0: " << this->getV0()
    << " v1: " << this->getV1() 
    << " v2: " << this->getV2() << std::endl
    << "n0: " << n0
    << " n1: " << n1
    << " n2: " << n2 << std::endl
    << "material: " << this->getMaterial() << std::endl;
}
