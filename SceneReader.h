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
       
    public:
        SceneReader();
        int readFile(std::string fileName);
        friend std::ostream& operator<<(std::ostream& out, const SceneReader& sceneReader);
};
