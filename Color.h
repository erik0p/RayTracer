#pragma once

#include <iostream>

class Color {
    private:
        float r;
        float g;
        float b;

    public:

        Color();

        /*
         * Constructor for color.
         *
         * @param r_ the red value 0-1
         * @param g_ the green value 0-1
         * @param b_ the blue value 0-1
         */
        Color(int r_, int g_, int b_);

        float getR() const { return r; }
        float getG() const { return g; }
        float getB() const { return b; }

        /*
         * Linearly interpolates between two colors, c1 and c2, by the amount t.
         *
         * @param c1 first color to interpolate between
         * @param c2 second color to interpolate between
         * @param t the amount to interpolate by
         * @return the color resulting from interpolating between c1 and c2 by amount t
         */
        static Color lerp(const Color& c1, const Color& c2, float t);

        /*
         * Overload the out stream operator to print the RGB values in a format usable by .ppm files
         *
         * @param out the outstream
         * @param color the color whose RGB values are printed
         */
        friend std::ostream& operator<<(std::ostream& out, const Color& color);
};
