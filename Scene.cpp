#include "Scene.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vector3.h"
#include <cfloat>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

Scene::Scene() {}
Scene::~Scene() {
    for (Object* obj : objects) {
        delete obj;
    }
    objects.clear();
}

const double PI = 3.14159265358979323846;

int Scene::initializeScene(std::string fileName) {
    std::ifstream inputFile(fileName);
    std::string read;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, read)) {
            std::stringstream ss(read);
            std::string keyword;
            ss >> keyword;

            if (keyword.compare("eye") == 0) {
                float x, y, z;
                ss >> x;
                ss >> y;
                ss >> z;
                if (ss.fail()) {
                    std::cout << "Invalid input for eye parameter. Must provide three floats 'eye x y z'" << std::endl;
                    return -1;
                }
                eye = Vector3(x, y, z);

            } else if (keyword.compare("viewdir") == 0) {
                float x, y, z;
                ss >> x;
                ss >> y;
                ss >> z;
                if (ss.fail()) {
                    std::cout << "Invalid input for viewdir parameter. Must provide three floats 'viewdir x y z'" << std::endl;
                    return -1;
                }
                viewdir = Vector3(x, y, z);

            } else if (keyword.compare("updir") == 0) {
                float x, y, z;
                ss >> x;
                ss >> y;
                ss >> z;
                if (ss.fail()) {
                    std::cout << "Invalid input for updir parameter. Must provide three floats 'updir x y z'" << std::endl;
                    return -1;
                }
                updir = Vector3(x, y, z);

            } else if (keyword.compare("vfov") == 0) {
                float fov;
                ss >> fov;
                if (ss.fail()) {
                    std::cout << "Invalid input for vfov parameter. Must provide a float 'vfov degrees'" << std::endl;
                    return -1;
                }
                vfov = fov;
            } else if (keyword.compare("imsize") == 0) {
                int imgWidth_, imgHeight_;
                ss >> imgWidth_;
                ss >> imgHeight_;
                if (ss.fail() || imgWidth_ < 0 || imgHeight_ < 0) {
                    std::cout << "Invalid input for imsize parameter. Must provide two positive integers 'imsize width height'" << std::endl;
                    return -1;
                }
                imgWidth = imgWidth_;
                imgHeight = imgHeight_;

            } else if (keyword.compare("bkgcolor") == 0) {
                float r, g, b;
                ss >> r;
                ss >> g;
                ss >> b;
                if (ss.fail()) {
                    std::cout << "Invalid input for bkgcolor parameter. Must provide three floats 'bkgcolor r g b'" << std::endl;
                    return -1;
                }
                bkgcolor = Color(r, g, b);

            } else if (keyword.compare("mtlcolor") == 0) {
                float r, g, b;
                ss >> r;
                ss >> g;
                ss >> b;
                if (ss.fail()) {
                    std::cout << "Invalid input for mtlcolor parameter. Must provide three floats 'mtlcolor r g b'" << std::endl;
                    return -1;
                }
                mtlcolor = Color(r, g, b);

            } else if (keyword.compare("sphere") == 0) {
                float x, y, z, r;
                ss >> x;
                ss >> y;
                ss >> z;
                ss >> r;
                if (ss.fail()) {
                    std::cout << "Invalid input for sphere parameter. Must provide four floats 'sphere x y z r'" << std::endl;
                    return -1;
                }
                Vector3 center(x, y, z);
                Color color = mtlcolor;
                Sphere* sphere = new Sphere(center, r, color);
                objects.push_back(sphere);
            }
        }
    } else {
        return -1;
    }
    inputFile.close();

    // initialize v (vertical vector) and u (horizontal vector)
    // viewdir.normalize();
    // updir.normalize();
    u = Vector3::cross(viewdir, updir);
    u.normalize();
    v = Vector3::cross(u, viewdir);
    v.normalize();
    std::cout << "u dot v = " << u.dot(v) << std::endl;
    std::cout << "u dot viewdir = " << u.dot(viewdir) << std::endl;
    std::cout << "u dot updir = " << u.dot(updir) << std::endl;

    // unit vector in viewdir
    Vector3 n = viewdir.normalized();

    float degToRad = PI / 180.0f;
    float aspectRatio = imgWidth / imgHeight;
    float d = imgHeight / 2.0f / tan(0.5f * vfov * degToRad);
    std::cout << "distance: " << d << std::endl;
    viewHeight = 2.0f * d * tan(0.5f * vfov * degToRad);
    viewWidth = viewHeight * aspectRatio;

    std::cout << "view: " << viewHeight / viewWidth << std::endl;
    std::cout << "image: " << imgHeight / imgWidth << std::endl;

    ul = eye + d * n - (viewWidth / 2.0f) * u + (viewHeight / 2.0f) * v;
    ur = eye + d * n + (viewWidth / 2.0f) * u + (viewHeight / 2.0f) * v;
    ll = eye + d * n - (viewWidth / 2.0f) * u - (viewHeight / 2.0f) * v;
    lr = eye + d * n + (viewWidth / 2.0f) * u - (viewHeight / 2.0f) * v;

    return 0;
}

Vector3 Scene::imageToView(int row, int col) {
    Vector3 deltaH = (ur - ul) / (imgWidth - 1.0f);
    Vector3 deltaV = (ll - ul) / (imgHeight - 1.0f);
    // Vector3 deltaH = (ur - ul) / (imgWidth);
    // Vector3 deltaV = (ll - ul) / (imgHeight);
    // Vector3 h = (ur - ul) / (2.0f * imgWidth);
    // Vector3 v = (ll - ul) / (2.0f * imgHeight);

    Vector3 result = ul + deltaH * static_cast<float>(col) + deltaV * static_cast<float>(row);
        
    return result;
}

Color Scene::traceRay(const Ray& ray) const {
    Color color = bkgcolor;
    Object *closestObject = NULL;
    float minT = FLT_MAX;
    
    for (Object* obj : objects) {
        float t = FLT_MAX;
        if (obj->rayIntersects(ray, t)) {
            if (t < minT && t > 0.0f) {
                minT = t;
                closestObject = obj;
            }
        }
    }
    if (closestObject != NULL) {
        color = closestObject->getColor();
    }

    return color;
}

std::ostream &operator<<(std::ostream& out, const Scene& scene) {
    out << "scene: " << std::endl
        << "eye: " << scene.eye << std::endl
        << "viewdir: " << scene.viewdir << std::endl
        << "updir: " << scene.updir << std::endl
        << "vfov: " << scene.vfov << std::endl
        << "imgWidth: " << scene.imgWidth << std::endl
        << "imgHeight: " << scene.imgHeight << std::endl
        << "bkgcolor: " << scene.bkgcolor << std::endl
        << "mtlcolor: " << scene.mtlcolor << std::endl
        << "u: " << scene.u << std::endl
        << "v: " << scene.v << std::endl
        << "viewHeight: " << scene.viewHeight << std::endl
        << "viewWidth: " << scene.viewWidth << std::endl
        << "ul: " << scene.ul << std::endl
        << "ur: " << scene.ur << std::endl
        << "ll: " << scene.ll << std::endl
        << "lr: " << scene.lr << std::endl;
    for (Object* obj : scene.objects) {
        obj->print(out);
        out << std::endl;
    }
    return out;
}
