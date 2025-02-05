#include <ostream>
#include <cmath>
#include "Point3.h"

Point3::Point3() {
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;
}

Point3::Point3(float x_, float y_, float z_) {
    x = x_;
    y = y_;
    z = z_;
}

float Point3::distanceBetween(const Point3 p1, const Point3 p2) {
    return sqrt(
            (p1.x - p2.x) * (p1.x - p2.x) +
            (p1.y - p2.y) * (p1.y - p2.y) +
            (p1.z - p2.z) * (p1.z - p2.z)
            );
}

std::ostream& operator<<(std::ostream& out, const Point3& point3) {
    out << "point3: " << "x: " << point3.x << " y: " << point3.y << " z: " << point3.z;
    return out;
}
