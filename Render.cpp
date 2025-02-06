#include "Ray.h"
#include "Scene.h"
#include "Vector3.h"
#include <fstream>
#include <iostream>

std::string truncateSuffix(std::string str) {
    return str.erase(str.length() - 4, str.length());
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Must provide a file name" << std::endl;
        return 0;
    } else if (argc > 2) {
        std::cout << "Provide only one file" << std::endl;
        return 0;
    }

    // Get file name provided from command line
    std::string fileName = argv[1];
    Scene scene;
    if (scene.initializeScene(fileName) == -1) {
        std::cout << "Unable to read file" << std::endl;
        return 0;
    }
    std::cout << scene;

    // Remove .txt from file name
    std::string truncatedName = truncateSuffix(fileName);
    // Create .ppm file
    std::ofstream outputFile(truncatedName + ".ppm");
    if (outputFile.is_open()) {
        outputFile << "P3" << std::endl;
        outputFile << "# Raycaster" << std::endl;
        outputFile << scene.getImgWidth() << " " << scene.getImgHeight() << std::endl;
        outputFile << "255" << std::endl;

        for (int row = 0; row < scene.getImgHeight(); row++) {
            /*std::cout << "row " << row << " ";*/
            for (int col = 0; col < scene.getImgWidth(); col++) {
                /*std::cout << scene.imageToView(row, col) << " ";*/

                Vector3 dir = scene.imageToView(row, col) - scene.getEye();
                dir.normalize();

                Vector3 origin = scene.getEye();
                Ray ray(origin, dir);

                Color pxColor = scene.traceRay(ray);
                outputFile << pxColor << std::endl;
            }
            /*std::cout << std::endl;*/
        }
        outputFile.close();
    }
    return 0;
}
