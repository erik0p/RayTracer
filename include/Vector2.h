#pragma once


class Vector2 {
    private:
        float x;
        float y;
    public:
        Vector2();
        Vector2(float x_, float y_);
        float getX() const { return x; }
        float getY() const { return y; }
};