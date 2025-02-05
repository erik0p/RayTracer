#include <iostream>
#include "Color.h"

Color::Color() {
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
}

Color::Color(float r_, float g_, float b_) {
    if (r_ < 0.0f) r_ = 0.0f;
    if (g_ < 0.0f) g_ = 0.0f;
    if (b_ < 0.0f) b_ = 0.0f;
    if (r_ > 1.0f) r_ = 1.0f;
    if (g_ > 1.0f) g_ = 1.0f;
    if (b_ > 1.0f) b_ = 1.0f;

    r = r_;
    g = g_;
    b = b_;
}

Color Color::lerp(const Color& c1, const Color& c2, float t) {
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    float r_ = c1.getR() + t * (c2.getR() - c1.getR());
    float g_ = c1.getG() + t * (c2.getG() - c1.getG());
    float b_ = c1.getB() + t * (c2.getB() - c1.getB());

    return Color(r_, g_, b_);
}

std::ostream& operator<<(std::ostream& out, const Color& color) {
    int r_ = color.r * 255.0f;
    int g_ = color.g * 255.0f;
    int b_ = color.b * 255.0f;

    out << r_ << " " << g_ << " " << b_;
    return out;
}
