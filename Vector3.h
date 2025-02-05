#pragma once
#include <ostream>

class Vector3 {
private:
  float x;
  float y;
  float z;

public:
  const static Vector3 UP;
  const static Vector3 ZERO;
  Vector3();
  Vector3(float x_, float y_, float z_);

  float getX() const { return x; }
  float getY() const { return y; }
  float getZ() const { return z; }
  float length() const;
  void normalize();
  Vector3 normalized() const;
  static float distanceBetween(const Vector3 &v1, const Vector3 &v2);
  static Vector3 add(const Vector3 &v1, const Vector3 &v2);
  static Vector3 subtract(const Vector3 &v1, const Vector3 &v2);
  static Vector3 multiply(float scalar, const Vector3 &v);
  static Vector3 cross(const Vector3 &v1, const Vector3 &v2);
  friend std::ostream &operator<<(std::ostream &out, const Vector3 &vector3);
};
