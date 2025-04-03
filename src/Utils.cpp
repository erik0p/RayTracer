#include "Utils.h"
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>

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

bool utils::readTextureFile(std::string ppmfile, std::vector<Material*>& materials) {
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
    // float ka = material.getKa();
    // float kd = material.getKd();
    // float ks = material.getKs();
    // float n = material.getN();
    // float opacity = material.getOpacity();
    // float refractionIndex = material.getRefractionIndex();
    // Color specularColor = material.getSpecularColor();
    float ka = materials.back()->getKa();
    float kd = materials.back()->getKd();
    float ks = materials.back()->getKs();
    float n = materials.back()->getN();
    float opacity = materials.back()->getOpacity();
    float refractionIndex = materials.back()->getRefractionIndex();
    Color specularColor = materials.back()->getSpecularColor();
    Material* material = new Material(ka, kd, ks, n, opacity, refractionIndex, specularColor, width, height, texture);
    materials.push_back(material);
    std::cout << "Read input/texture/" + ppmfile << std::endl;
    return true;
}