#pragma once

class Point3 {
    private:
        float x;
        float y;
        float z;

    public:
        Point3();
        Point3(float x_, float y_, float z_);

        float getX() const { return x; }
        float getY() const { return y; }
        float getZ() const { return z; }
        static float distanceBetween(const Point3 p1, const Point3 p2);
        friend std::ostream& operator<<(std::ostream& out, const Point3& point3);
};
