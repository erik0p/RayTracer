#include <ostream>
#include "Point3.h"

Point3::Point3(float x_, float y_, float z_) {
    x = x_;
    y = y_;
    z = z_;
}

std::ostream& operator<<(std::ostream& out, const Point3& point3) {
    out << "point3: " << "x: " << point3.x << " y: " << point3.y << " z: " << point3.z;
    return out;
}
