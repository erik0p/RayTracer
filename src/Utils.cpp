#include "Utils.h"
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>

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

bool utils::readTextureFile(std::string ppmfile, Material& material) {
    std::ifstream inputFile("input/texture/" + ppmfile);
    std::string read;
    int width, height, maxColor;
    std::vector<std::vector<Color>> texture;

    if (inputFile.is_open()) {
        std::string header;
        float r, g, b;
        inputFile >> header >> width >> height >> maxColor;

        if (header.compare("P3") != 0) {
            std::cout << "Inavlid header for " << ppmfile << std::endl;
            return false;
        }

        texture = std::vector<std::vector<Color>>(height, std::vector<Color>(width));

        // while (inputFile >> r >> g >> b) {
        //     Color color = Color(r / 255.0, g / 255.0 , b / 255.0);
        //     texture.push_back(std::vector<Color>(width));
        // }
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                inputFile >> r >> g >> b;
                Color color = Color(r / maxColor, g / maxColor, b / maxColor);
                texture[i][j] = color;
            }
        }
    } else {
        std::cout << "Unable to read " << ppmfile << std::endl;
        return false;
    }

    if (width == 0 || height == 0) {
        std::cout << "Invalid header for " << ppmfile << std::endl;
        return false;
    }
    float ka = material.getKa();
    float kd = material.getKd();
    float ks = material.getKs();
    float n = material.getN();
    Color specularColor = material.getSpecularColor();
    material = Material(ka, kd, ks, n, specularColor, width, height, texture);
    std::cout << "read input/texture/" + ppmfile << std::endl;
    return true;
}