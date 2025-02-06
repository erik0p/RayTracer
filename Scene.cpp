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

int Scene::initializeScene(std::string fileName) {
    std::ifstream inputFile(fileName);
    std::string read;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, read)) {
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
                int imgWidth_, imgHeight_;
                stringStream >> imgWidth_;
                stringStream >> imgHeight_;

                imgWidth = imgWidth_;
                imgHeight = imgHeight_;

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
    std::cout << "u " << u << std::endl;
    u.normalize();
    v = Vector3::cross(u, viewdir);
    std::cout << "v " << v << std::endl;
    v.normalize();

    // unit vector in viewdir
    Vector3 n = viewdir.normalized();

    float degToRad = M_PI / 180.0f;
    float aspectRatio = imgWidth / imgHeight;
    float d = 5.0f;
    viewHeight = 2.0f * d * tan(0.5f * vfov * degToRad);
    viewWidth = viewHeight * aspectRatio;

    std::cout << "view: " << viewHeight / viewWidth << std::endl;
    std::cout << "image: " << imgHeight / imgWidth << std::endl;

    ul = eye + n * d - u * (viewWidth / 2.0f) + v * (viewHeight / 2.0f);
    ur = eye + n * d + u * (viewWidth / 2.0f) + v * (viewHeight / 2.0f);
    ll = eye + n * d - u * (viewWidth / 2.0f) - v * (viewHeight / 2.0f);
    lr = eye + n * d + u * (viewWidth / 2.0f) - v * (viewHeight / 2.0f);

    return 0;
}

Vector3 Scene::imageToView(int row, int col) {
    Vector3 deltaH = (ur - ul) / (imgWidth - 1.0f);
    Vector3 deltaV = (ll - ul) / (imgHeight - 1.0f);

    Vector3 result = ul + deltaH * static_cast<float>(col) + deltaV * static_cast<float>(row);
    return result;
}

Color Scene::traceRay(const Ray& ray) const {
    Color color = bkgcolor;
    Vector3 v;
    Sphere closestSphere(v, 0, color);
    float minT = FLT_MAX;

    for (const Sphere &sphere : spheres) {
        float x = ray.getOrigin().getX();
        float y = ray.getOrigin().getY();
        float z = ray.getOrigin().getZ();
        float dx = ray.getDir().getX();
        float dy = ray.getDir().getY();
        float dz = ray.getDir().getZ();
        float cx = sphere.getCenter().getX();
        float cy = sphere.getCenter().getY();
        float cz = sphere.getCenter().getZ();

        float a = 1.0f;
        float b = 2.0f * (dx * (x - cx) + dy * (y - cy) + dz * (z - cz));
        float c = pow(x - cx, 2) + pow(y - cy, 2) + pow(z - cz, 2) - pow(sphere.getRadius(), 2);
        float t1 = -b + sqrt(pow(b, 2) - 4.0f * c) / 2.0f;
        float t2 = -b - sqrt(pow(b, 2) - 4.0f * c) / 2.0f;
        float discriminant = pow(b, 2) - 4.0f * a * c;

        if (discriminant > 0.0f) {
            if (t1 < minT && t1 > 0.0f) {
                minT = t1;
                closestSphere = sphere;
            }
            if (t2 < minT && t2 > 0.0f) {
                minT = t2;
                closestSphere = sphere;
            }
        }
    }

    return closestSphere.getColor();
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
    for (const Sphere &s : scene.spheres) {
        out << s << std::endl;
    }
    return out;
}
