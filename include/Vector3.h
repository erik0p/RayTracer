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

  /**
   * constructor for vector3
   *
   * @param x_ the x component
   * @param y_ the y component
   * @param z_ the z component
   * 
   */
  Vector3(float x_, float y_, float z_);

  float getX() const { return x; }
  float getY() const { return y; }
  float getZ() const { return z; }

  /**
   * overload the addition operator for vector addition
   *
   * @param v a vector3
   * 
   * @return result of adding v to the vector3
   */
  Vector3 operator+(const Vector3& v) const;

  /**
   * overload the subtraction operator for vector subtraction
   *
   * @param v a vector3
   * 
   * @return result of subtracting v from the vector3
   */
  Vector3 operator-(const Vector3& v) const;

  /**
   * overload the multiplication operator for vector scalar multiplication where the scalar comes first
   *
   * @param scalar the scalar value
   * @param rhs the rhs vector3
   * 
   * @return the result of multiplying the vector3 by a scalar
   */
  friend Vector3 operator*(const float& scalar, const Vector3& rhs);

  /**
   * overload the multiplication operator for vector scalar multiplication
   *
   * @param scalar the scalar value 
   * 
   * @return the result of multiplying the vector3 by a scalar
   */
  Vector3 operator*(const float& scalar);

  /**
   * overload the division operator for vector scalar division
   *
   * @param scalar the scalar value
   *
   * @return the result of dividing the vector3 by a scalar
   */
  Vector3 operator/(const float& scalar);

  /**
   * calculates the magnitude of the vector3
   *
   * @return the magnitude of the vector3
   */
  float length() const;

  /**
   * normalizes the vector3
   *
   */
  void normalize();

  /**
   * calculates a vector3 that is normalized
   *
   * 
   * @return a normalized vector3
   */
  Vector3 normalized() const;

  /**
   * calculates the dot product with another vector3
   *
   * @param v the vector3 to dot with
   * 
   * @return the result of the dot product with v
   */
  float dot(const Vector3& v) const;

  /**
   * determines if the x, y, z components of two vector3s are equal
   *
   * @param v1 a vector3
   * @param v2 a vector3
   * 
   * @return true if two vector3s are equal, false otherwise
   */
  bool equals(const Vector3& v) const;

  /**
   * calculates the euclidean distance between two vectors
   *
   * @param v1 the lhs vector3
   * @param v2 the rhs vector3
   * 
   * @return the distance between v1 and v2
   */
  static float distanceBetween(const Vector3& v1, const Vector3& v2);

  /**
   * performs addition between two vector3s
   *
   * @param v1 the lhs vector3
   * @param v2 the rhs vector3
   * 
   * @return the result of v1 added with v1
   */
  static Vector3 add(const Vector3& v1, const Vector3& v2);

  /**
   * performs subtraction between two vector3s
   *
   * @param v1 the lhs vector3
   * @param v2 the rhs vector3
   * 
   * @return the result of v2 subtracted from v1
   */
  static Vector3 subtract(const Vector3& v1, const Vector3& v2);

  /**
   * performs scalar multiplication on a vector3
   *
   * @param scalar the scalar value
   * @param v the vector3 to multiply
   * 
   * @return the result of multipling the vector3 by the scalar
   */
  static Vector3 multiply(float scalar, const Vector3& v);

  /**
   * performs the cross product of two vector3s
   *
   * @param v1 the lhs vector3
   * @param v2 the rhs vector3
   * 
   * @return the result of v1 crossed with v2
   */
  static Vector3 cross(const Vector3& v1, const Vector3& v2);

  /**
   * Overload the out stream operator to print a vector3
   *
   * @param out the outstream
   * @param vector3 the vector3 whose fields are printed
   */
  friend std::ostream &operator<<(std::ostream& out, const Vector3& vector3);
};
