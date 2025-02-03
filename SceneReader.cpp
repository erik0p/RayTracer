#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "SceneReader.h"
#include "Vector3.h"
#include "Point3.h"
#include "Sphere.h"

SceneReader::SceneReader() {
}

int SceneReader::readFile(std::string fileName) {
    std::ifstream inputFile(fileName);
    std::string read;

    if (inputFile.is_open()) {
        while(std::getline(inputFile, read)) {
            std::stringstream stringStream(read);
            std::string keyword;
            stringStream >> keyword;

            if (keyword.compare("eye") == 0) {
                float x, y, z;
                stringStream >> x;
                stringStream >> y;
                stringStream >> z; 
                eye = Vector3(x, y, z);
            } else if (keyword.compare("viewdir") == 0) {
                float x, y, z;
                stringStream >> x;
                stringStream >> y;
                stringStream >> z; 
                viewdir = Vector3(x, y, z);

            } else if (keyword.compare("updir") == 0) {
                float x, y, z;
                stringStream >> x;
                stringStream >> y;
                stringStream >> z; 
                updir = Vector3(x, y, z);

            } else if (keyword.compare("vfov") == 0) {
                float fov;
                stringStream >> fov;
                vfov = fov;
            } else if (keyword.compare("imsize") == 0) {
                int width_, height_;
                stringStream >> width_;
                stringStream >> height_;
                
                width = width_;
                height = height_;

            } else if (keyword.compare("bkgcolor") == 0) {
                float r, g, b;
                stringStream >> r;
                stringStream >> g;
                stringStream >> b;
                bkgcolor = Color(r, g, b);

            } else if (keyword.compare("mtlcolor") == 0) {
                float r, g, b;
                stringStream >> r;
                stringStream >> g;
                stringStream >> b;
                mtlcolor = Color(r, g, b);

            } else if (keyword.compare("sphere") == 0) {
                float x, y, z, r;
                stringStream >> x;
                stringStream >> y;
                stringStream >> z; 
                stringStream >> r; 
                Point3 center(x, y, z);
                Sphere sphere(center, r);
                spheres.push_back(sphere);
            }
        }
    } else {
        return -1;
    }
    inputFile.close();
    return 0;
}

std::ostream& operator<<(std::ostream& out, const SceneReader& sceneReader) {
    out << "scene: " << std::endl
        << "eye: " << sceneReader.eye << std::endl
        << "viewdir: " << sceneReader.viewdir << std::endl
        << "updir: " << sceneReader.updir << std::endl
        << "vfov: " << sceneReader.vfov << std::endl
        << "width: " << sceneReader.width << std::endl
        << "height: " << sceneReader.height << std::endl
        << "bkgcolor: " << sceneReader.bkgcolor << std::endl
        << "mtlcolor: " << sceneReader.mtlcolor << std::endl;
        for (const Sphere& s : sceneReader.spheres) {
            out << s << std::endl;
        }
    return out;
}
