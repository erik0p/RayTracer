#include <ostream>
#include "Vector3.h"

Vector3::Vector3() {
    x = 0;
    y = 0;
    z = 0;
}

Vector3::Vector3(float x_, float y_, float z_) {
    x = x_;
    y = y_;
    z = z_;
}

std::ostream& operator<<(std::ostream& out, const Vector3& vector3) {
    out << "vector3: " << "x: " << vector3.x << " y: " << vector3.y << " z: " << vector3.z;
    return out;
}
