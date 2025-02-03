#pragma once
#include <vector>
#include <ostream>
#include "Vector3.h"
#include "Color.h"
#include "Sphere.h"

class SceneReader {
    private:
        Vector3 eye;
        Vector3 viewdir;
        Vector3 updir;
        float vfov;
        int width;
        int height;
        Color bkgcolor;
        Color mtlcolor;
        std::vector<Sphere> spheres;

        /*Vector3 readEye(std::string line);*/
        /*Vector3 readViewdir(std::string line);*/
        /*Vector3 readUpdir(std::string line);*/
        /*float readVfov(std::string line);*/
        /*int readWidth(std::string line);*/
        /*int readHeight(std::string line);*/
        /*Color readBkgcolor(std::string line);*/
        /*Color readMtlcolor(std::string line);*/
       
    public:
        SceneReader();
        int readFile(std::string fileName);
        friend std::ostream& operator<<(std::ostream& out, const SceneReader& sceneReader);
};
