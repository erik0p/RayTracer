#pragma once

class Point3 {
    private:
        float x;
        float y;
        float z;

    public:
        Point3(float x_, float y_, float z_);

        float getX() const { return x; }
        float getY() const { return y; }
        float getZ() const { return z; }
        friend std::ostream& operator<<(std::ostream& out, const Point3& point3);
};
