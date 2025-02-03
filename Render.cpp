#include <iostream>
#include <fstream>
#include <sstream>
#include "SceneReader.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Must provide a file name" << std::endl;
        return 0;
    } else if (argc > 2) {
        std::cout << "Provide only one file" << std::endl;
        return 0;
    }

    // Get file name provided from command line
    std::string fileName = argv[1];
    SceneReader scene;
    if (scene.readFile(fileName) == -1) {
        std::cout << "Unable to read file" << std::endl;
        return 0;
    }
    std::cout << scene;
    return 0;
}
