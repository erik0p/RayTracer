#include "Utils.h"
#include "Ray.h"
#include "Scene.h"
#include "Vector3.h"
#include <fstream>
#include <string>
#include <iostream>

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

    std::cout << "---------------------------" << std::endl;
    std::cout << "Reading input description from " << fileName << std::endl;
    std::cout << "---------------------------" << std::endl << std::endl;
    if (scene.initializeScene(fileName) == -1) { // check file was read successfully
        std::cout << "Unable to read " << fileName << std::endl;
        return 0;
    }
    std::cout << "Successfully read input description" << std::endl << std::endl;; 

    // debug
    // std::cout << scene;

    // Remove .txt from file name
    std::string truncatedName = utils::truncateSuffix(fileName);
    // Create .ppm file
    std::ofstream outputFile(truncatedName + ".ppm");

    if (outputFile.is_open()) {
        outputFile << "P3" << std::endl;
        outputFile << "# Raytracer" << std::endl;
        outputFile << scene.getImgWidth() << " " << scene.getImgHeight() << std::endl;
        outputFile << "255" << std::endl;

        std::cout << "---------------------------" << std::endl;
        std::cout << "Rendering image..." << std::endl;
        std::cout << "---------------------------" << std::endl << std::endl;

        // Color in each pixel in the image
        for (int row = 0; row < scene.getImgHeight(); row++) {
            for (int col = 0; col < scene.getImgWidth(); col++) {
                
                Vector3 viewPoint = scene.imageToView(row, col);
                Vector3 dir = viewPoint - scene.getEye();
                dir.normalize();

                Vector3 origin = scene.getEye();
                Ray ray(origin, dir);

                Color pxColor = scene.traceRay(ray);
                outputFile << pxColor << std::endl;
            }
            std::cout << (int(row / scene.getImgHeight() * 100)) << "%\r";
        }
        outputFile.close();
    }
    std::cout << "Done!" << std::endl;
    return 0;
}
