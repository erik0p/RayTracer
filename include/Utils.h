#pragma once
#include <string>
#include "Material.h"

namespace utils {
    const double PI = 3.14159265358979323846;

    /**
     * converts from degrees to radians
     *
     * @param deg the degree
     *
     * @return the conversion of deg to radians
     */
    float degToRad(float deg);

    /**
     * removes the last 4 characters of a string to truncate the file extension
     *
     * @param str the string to truncate
     *
     * @return the truncated string
     */
    std::string truncateSuffix(std::string str);

    /**
     * determines if a string contains whitespace or is empty
     *
     * @param str the string to check
     *
     * @return true if str contains whitespace or is empty, false otherwise
     */
    bool containsWhiteSpaceOrEmpty(std::string str);

    bool readTextureFile(std::string ppmfile, Material& material);
}