#include "Vector3.h"
#include <cmath>
#include <ostream>

const Vector3 Vector3::UP = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::ZERO = Vector3(0.0f, 0.0f, 0.0f);

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

Vector3 Vector3::operator+(const Vector3& v) const {
    return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3& v) const {
    return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator*(const float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

Vector3 Vector3::operator/(const float scalar) const {
    return Vector3(x / scalar, y / scalar, z / scalar);
}

float Vector3::length() const {
    return sqrt(x * x + y * y + z * z);
}

void Vector3::normalize() {
    float len = this->length();
    if (len != 0.0f) {
        x = x / len;
        y = y / len;
        z = z / len;
    }
}

Vector3 Vector3::normalized() const {
    float len = this->length();
    if (len == 0.0f) {
        return Vector3::ZERO;
    }
    return Vector3(x / len, y / len, z / len);
}

float Vector3::distanceBetween(const Vector3& v1, const Vector3& v2) {
    return sqrt(
            (v1.x - v2.x) * (v1.x - v2.x) + 
            (v1.y - v2.y) * (v1.y - v2.y) +
            (v1.z - v2.z) * (v1.z - v2.z)
            );
}

Vector3 Vector3::add(const Vector3& v1, const Vector3& v2) {
    return Vector3(
            v1.x + v2.x,
            v1.y + v2.y,
            v1.z + v2.z);
}

Vector3 Vector3::subtract(const Vector3& v1, const Vector3& v2) {
    return Vector3(
            v1.x - v2.x,
            v1.y - v2.y,
            v1.z - v2.z
            );
}

Vector3 Vector3::multiply(float scalar, const Vector3& v) {
    return Vector3(v.x * scalar, v.y * scalar, v.z * scalar);
}

Vector3 Vector3::cross(const Vector3& v1, const Vector3& v2) {
    return Vector3(
            v1.y * v2.z - v1.z * v2.y,
            v1.z * v2.x - v1.x * v2.z,
            v1.x * v2.y - v1.y * v2.x
            );
}

std::ostream &operator<<(std::ostream& out, const Vector3& vector3) {
    out << "vector3: " << "x: " << vector3.x << " y: " << vector3.y
        << " z: " << vector3.z;
    return out;
}
