#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "SceneReader.h"
#include "Vector3.h"
#include "Sphere.h"
#include "Ray.h"

SceneReader::SceneReader() {
}

int SceneReader::initializeScene(std::string fileName) {
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
                Vector3 center(x, y, z);
                Color color = mtlcolor;
                Sphere sphere(center, r, color);
                spheres.push_back(sphere);
            }
        }
    } else {
        return -1;
    }
    inputFile.close();

    // initialize v (vertical vector) and u (horizontal vector)
    u = Vector3::cross(viewdir, updir);
    u.normalize();
    v = Vector3::cross(u, viewdir);
    v.normalize();

    // unit vector in viewdir
    Vector3 n = viewdir.normalized();
    float d = 5.0f;
    
    float degToRad = M_PI / 180.0f;
    float aspectRatio = width / height;
    viewHeight = 2 * d * tan(0.5 * vfov * degToRad);
    viewWidth = viewHeight * aspectRatio;
    
    Vector3 eyePlusDN = Vector3::add(eye, Vector3::multiply(d, n));
    Vector3 scaleU = Vector3::multiply(viewWidth / 2.0f, u);
    Vector3 scaleV = Vector3::multiply(viewHeight / 2.0f, v);

    ul = Vector3::add(Vector3::subtract(eyePlusDN, scaleU), scaleV);
    ur = Vector3::add(eyePlusDN, Vector3::add(scaleU, scaleV));
    ll = Vector3::subtract(Vector3::subtract(eyePlusDN, scaleU), scaleV);
    lr = Vector3::add(eyePlusDN, Vector3::add(scaleU, scaleV));

    return 0;
}

Vector3 SceneReader::imageToView(int row, int col) {
    Vector3 deltaH = Vector3::multiply(1.0f / (width - 1.0f), Vector3::subtract(ur, ul));
    Vector3 deltaV = Vector3::multiply(1.0f / (height - 1.0f), Vector3::subtract(ll, ul));

    Vector3 result = Vector3::add(ul, Vector3::add(Vector3::multiply(static_cast<float>(row), deltaH), Vector3::multiply(static_cast<float>(col), deltaV)));
    return result;
}

Color SceneReader::traceRay(const Ray& ray) const {
    Color color;

    for (const Sphere& sphere : spheres) {
        float dirX = ray.getDir().getX();
        float dirY = ray.getDir().getY();
        float dirZ = ray.getDir().getZ();

        float originMinusCenterX = ray.getOrigin().getX() - sphere.getCenter().getX();
        float originMinusCenterY = ray.getOrigin().getY() - sphere.getCenter().getY();
        float originMinusCenterZ = ray.getOrigin().getZ() - sphere.getCenter().getZ();

        float a = dirX * dirX + dirY * dirY + dirZ * dirZ;
        float b = 2.0f * (dirX * (originMinusCenterX)
                        + dirY * (originMinusCenterY) 
                        + dirZ * (originMinusCenterZ));
        float c = originMinusCenterX * originMinusCenterX 
                    + originMinusCenterY * originMinusCenterY 
                    + originMinusCenterZ * originMinusCenterZ 
                    - sphere.getRadius() * sphere.getRadius();

        if (b * b - 4.0f * a * c > 0.0f) {
            color = sphere.getColor();
        }
    }

    color = bkgcolor;
    return color;
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
        << "mtlcolor: " << sceneReader.mtlcolor << std::endl
        << "u: " << sceneReader.u << std::endl
        << "v: " << sceneReader.v << std::endl
        << "viewHeight: " << sceneReader.viewHeight << std::endl
        << "viewWidth: " << sceneReader.viewWidth << std::endl
        << "ul: " << sceneReader.ul << std::endl
        << "ur: " << sceneReader.ur << std::endl
        << "ll: " << sceneReader.ll << std::endl
        << "lr: " << sceneReader.lr << std::endl
        ;
        for (const Sphere& s : sceneReader.spheres) {
            out << s << std::endl;
        }
    return out;
}
