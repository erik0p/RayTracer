#include "Utils.h"
#include <string>
#include <cctype>

float utils::degToRad(float deg) {
    return deg * PI / 180.0f;
}

std::string utils::truncateSuffix(std::string str) {
    return str.erase(str.length() - 4, str.length());
}

bool utils::containsWhiteSpaceOrEmpty(std::string str) {
    if (str.empty()) {
        return true;
    }
    for (char c : str) {
        if (isspace(c)) {
            return true;
        }
    }
    return false;
}