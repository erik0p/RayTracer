#include "Scene.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "AttenuationLight.h"
#include "Ray.h"
#include "Sphere.h"
#include "Vector3.h"
#include "Utils.h"
#include "Light.h"
#include "DepthCueing.h"
#include <cfloat>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <random>

Scene::Scene() {}
Scene::~Scene() {
    for (Sphere* sphere : objects) {
        delete sphere;
    }
    objects.clear();
    for (Light* light : lights) {
        delete light;
    }
    lights.clear();
}

int Scene::initializeScene(std::string fileName) {
    std::ifstream inputFile(fileName);
    std::string read;

    // initialize flags
    depthCueingFlag = false;

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
                float odr, odg, odb, osr, osg, osd, ka, kd, ks, n;
                ss >> odr;
                ss >> odg;
                ss >> odb;
                ss >> osr;
                ss >> osg;
                ss >> osd;
                ss >> ka;
                ss >> kd;
                ss >> ks;
                ss >> n;
                if (ss.fail()) {
                    std::cout << "Invalid input for mtlcolor parameter. " <<
                    "Must provide 10 floats 'mtlcolor odr odg odb osr osg osb ka kd ks n'" << std::endl;
                    return -1;
                }
                mtlcolor = Material(Color(odr, odg, odb), Color(osr, osg, osd), ka, kd, ks, n);
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
                Material material = mtlcolor;
                Sphere* sphere = new Sphere(center, r, material);
                objects.push_back(sphere);
            } else if (keyword.compare("light") == 0) {
                float x, y, z, i;
                int w;
                ss >> x;
                ss >> y;
                ss >> z;
                ss >> w;
                ss >> i;
                if (ss.fail()) {
                    std::cout << "Invalid input for light parameter. Must provide 5 floats 'light x y z w i'" << std::endl;
                    return -1;
                }
                Light* light;
                if (w == 1) {
                    light = new PointLight(Vector3(x, y, z), i);
                } else {
                    light = new DirectionalLight(Vector3(x, y, z), i);
                }
                lights.push_back(light);
            } else if (keyword.compare("depthcueing") == 0) {
                float r, g, b, aMin, aMax, distMin, distMax;
                ss >> r;
                ss >> g;
                ss >> b;
                ss >> aMin;
                ss >> aMax;
                ss >> distMin;
                ss >> distMax;
                if (ss.fail()) {
                    std::cout << "Invalid input for depthcueing parameter. Must provide 7 floats 'depthcueing r g b aMin aMax distMin distMax'" << std::endl;
                    return -1;
                }
                Color color = Color(r, g, b);
                depthCue = DepthCueing(color, aMin, aMax, distMin, distMax);
                depthCueingFlag = true;
            } else if (keyword.compare("attlight") == 0) {
                float x, y, z, w, i, c1, c2, c3;
                ss >> x;
                ss >> y;
                ss >> z;
                ss >> w;
                ss >> i;
                ss >> c1;
                ss >> c2;
                ss >> c3;
                if (ss.fail()) {
                    std::cout << "Invalid input for attlight parameter. Must provide 8 floats 'attlight x y z w i c1 c2 c3'" << std::endl;
                    return -1;
                }
                Light* light = new AttenuationLight(Vector3(x, y, z), i, c1, c2 ,c3);
                lights.push_back(light);
            } else if (!utils::containsWhiteSpaceOrEmpty(keyword)) {
                std::cout << keyword << " is not a valid keyword" << std::endl;
                return -1;
            } 
        }
    } else {
        return -1;
    }
    inputFile.close();

    // initialize v (vertical vector) and u (horizontal vector)
    viewdir.normalize();
    updir.normalize();

    u = Vector3::cross(viewdir, updir);
    u.normalize();
    v = Vector3::cross(u, viewdir);
    v.normalize();

    // unit vector in viewdir
    Vector3 n = viewdir;

    float aspectRatio = imgWidth / imgHeight;
    float d = 1.0f;
    viewHeight = 2.0f * d * tan(utils::degToRad(0.5f * vfov));
    viewWidth = viewHeight * aspectRatio;

    std::cout << "view aspect ratio: " << viewWidth / viewHeight << std::endl;
    std::cout << "image aspect ratio: " << aspectRatio << std::endl;

    // Find the point of each corner in the view window
    // +-*/ operators are overloaded to work with Vector3
    ul = eye + d * n - (viewWidth / 2.0f) * u + (viewHeight / 2.0f) * v;
    ur = eye + d * n + (viewWidth / 2.0f) * u + (viewHeight / 2.0f) * v;
    ll = eye + d * n - (viewWidth / 2.0f) * u - (viewHeight / 2.0f) * v;
    lr = eye + d * n + (viewWidth / 2.0f) * u - (viewHeight / 2.0f) * v;
    
    return 0;
}

// Go from image row and col to a point in view space
Vector3 Scene::imageToView(int row, int col) const {
    Vector3 deltaH = (ur - ul) / (imgWidth - 1.0f);
    Vector3 deltaV = (ll - ul) / (imgHeight - 1.0f);

    Vector3 result = ul + deltaH * static_cast<float>(col) + deltaV * static_cast<float>(row);
        
    return result;
}

Color Scene::traceRay(const Ray& ray) const {
    Color color = bkgcolor;
    Sphere *closestObject = NULL;
    float minT = FLT_MAX;
    
    // iterate through objects in the scene and find the object whose interesection is closest, if any
    for (Sphere* sphere : objects) {
        float t = FLT_MAX;
        if (sphere->rayIntersects(ray, t)) {
            if (t < minT && t > 0.0f) {
                minT = t;
                closestObject = sphere;
            }
        }
    }

    // get color of object if there was an intersection
    if (closestObject != NULL) {
        // color = closestObject->getMaterial().getDiffuseColor();
        Vector3 intersectionPoint;
        intersectionPoint = ray.getOrigin() + minT * ray.getDir();
        color = shadeRay(ray, closestObject->getMaterial(), intersectionPoint, *closestObject);
    }

    return color;
}

Color Scene::shadeRay(const Ray& ray, const Material& material, const Vector3& intersectionPoint, const Sphere& intersectedSphere) const {
    Color colorResult;
    float ka = material.getKa();
    float kd = material.getKd();
    float ks = material.getKs();
    float n = material.getN();
    Color diffuseColor = material.getDiffuseColor();
    Color specularColor = material.getSpecularColor();
    Color localIllumination(0.0f, 0.0f, 0.0f);
    int numberOfJitteredRays = 50;
    float jitterAmount = 0.01f;

    for (Light *light : lights)
    {

        Vector3 L; // vector pointing towards light source
        Vector3 N; // surface normal
        Vector3 H; // direction halfway between light and direction towards the viewer
        Vector3 V;
        float shadowFlag = 1.0f;

        L = light->getDirToSource(intersectionPoint);
        L.normalize();


        // std::cout << "shadowflag: " << shadowFlag << std::endl;
        // light->printInfo();

        if (!dynamic_cast<DirectionalLight*>(light)) { // Check if point light
            // std::cout << " L " << L << std::endl;
            for (int i = 0; i < numberOfJitteredRays; i++) {
                Vector3 jitteredLocation = jitterLocation(light->getDirOrCenter(), jitterAmount);
                PointLight jitteredLight = PointLight(jitteredLocation, light->getIntensity());
                Vector3 dirToLight = jitteredLight.getDirOrCenter() - intersectionPoint;
                dirToLight.normalize();

                // std::cout << "Jitter L " << dirToLight << std::endl;
                // std::cout << " jitter light ";
                // jitteredLight.printInfo();

                Ray shadowRay(intersectionPoint, dirToLight);
                shadowFlag += traceShadow(shadowRay, intersectedSphere, jitteredLight);
            }
            shadowFlag = shadowFlag / numberOfJitteredRays;
            // std::cout << "shadowflag: " << shadowFlag << std::endl;
        } else {
            Ray shadowRay(intersectionPoint, L);
            shadowFlag = traceShadow(shadowRay, intersectedSphere, *light);
        }

        N = (intersectionPoint - intersectedSphere.getCenter()) / intersectedSphere.getRadius();
        N.normalize();

        V = ray.getOrigin() - intersectionPoint;
        V.normalize();

        H = (L + V) / 2.0f;
        H.normalize();

        localIllumination = localIllumination + (shadowFlag * (kd * diffuseColor * std::max(0.0f, (N.dot(L))) + ks * specularColor * pow(std::max(0.0f, (N.dot(H))), n)));

        if (AttenuationLight* attLight = dynamic_cast<AttenuationLight*>(light)) {
            float distance = Vector3::distanceBetween(intersectionPoint, light->getDirOrCenter());
            float att = attLight->attenuation(distance);
            // std::cout << "att : " << att << std::endl;
            // std::cout << "distance : " << distance << std::endl;
            localIllumination = localIllumination * att;
        }
    }
    colorResult = ka * diffuseColor + localIllumination;

    if (depthCueingFlag) {
        float distance = Vector3::distanceBetween(eye, intersectionPoint);
        colorResult = depthCue.applyDepthCueing(colorResult, distance);
    }

    colorResult.clamp();

    return colorResult;
}

float Scene::traceShadow(const Ray& ray, const Sphere& originSphere, Light& light) const {
    float shadowFlag = 1.0f;
    
    // iterate through objects in the scene and find the object whose interesection is closest, if any
    for (Sphere* sphere : objects) {
        float t = FLT_MAX;

        if (!sphere->equals(originSphere)) { // don't check the sphere where the shadow ray originates
            // std::cout << "t before: " << t << std::endl;
            if (sphere->rayIntersects(ray, t)) {
            // std::cout << "t after: " << t << std::endl;

                if (t > 0.0f) {
                    if (dynamic_cast<DirectionalLight*>(&light)) {
                        shadowFlag = 0.0f;
                    } else {
                        float distance = Vector3::distanceBetween(ray.getOrigin(), light.getDirOrCenter());

                        if (t > distance) {
                            shadowFlag = 1.0f;
                        } else {
                            shadowFlag = 0.0f;
                        }
                    }
                }
            }
        }
    }

    return shadowFlag;
}

Vector3 Scene::jitterLocation(const Vector3& location, float jitterAmount) const {
    std::random_device rand;
    std::mt19937 gen(rand());
    std::uniform_real_distribution<> dis(-jitterAmount, jitterAmount);

    float xJitter = location.getX() + dis(gen);
    float yJitter = location.getY() + dis(gen);
    float zJitter = location.getZ() + dis(gen);

    return Vector3(xJitter, yJitter, zJitter);
}

    std::ostream &operator<<(std::ostream &out, const Scene &scene)
{
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
        << "lr: " << scene.lr << std::endl
        << "depthcueingflag: " << scene.depthCueingFlag << " " << scene.depthCue << std::endl;
    for (Sphere* sphere : scene.objects) {
        out << *sphere << std::endl;
    }
    for (Light* light : scene.lights) {
        // out << *light << std::endl;
        light->printInfo();
    }
    return out;
}
