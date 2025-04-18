#include "Scene.h"
#include "Object.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "AttenuationLight.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "SmoothShadedTriangle.h"
#include "Vector3.h"
#include "Vector2.h"
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
#include <regex>
#include <stack>

Scene::Scene() {}
Scene::~Scene() {
    for (Object* object : objects) {
        delete object;
    }
    objects.clear();
    for (Light* light : lights) {
        delete light;
    }
    lights.clear();
    for (Material* material : materials) {
        delete material;
    }
    materials.clear();
}

int Scene::initializeScene(std::string fileName) {
    std::ifstream inputFile(fileName);
    std::string read;

    // initialize flags
    depthCueingFlag = false;
    softShadowFlag = false;

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
                float r, g, b, refraction;
                ss >> r;
                ss >> g;
                ss >> b;
                ss >> refraction;
                if (ss.fail()) {
                    std::cout << "Invalid input for bkgcolor parameter. Must provide four floats 'bkgcolor r g b refraction'" << std::endl;
                    return -1;
                }
                bkgcolor = Material(Color(r, g, b), Color(), 0, 0, 0, 0, 0, refraction);

            } else if (keyword.compare("mtlcolor") == 0) {
                float odr, odg, odb, osr, osg, osd, ka, kd, ks, n, opacity, refraction;
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
                ss >> opacity;
                ss >> refraction;
                if (ss.fail()) {
                    std::cout << "Invalid input for mtlcolor parameter. " <<
                    "Must provide 12 floats 'mtlcolor odr odg odb osr osg osb ka kd ks n opacity refraction'" << std::endl;
                    return -1;
                }
                // mtlcolor = Material(Color(odr, odg, odb), Color(osr, osg, osd), ka, kd, ks, n, opacity, refraction);
                Material* mtl = new Material(Color(odr, odg, odb), Color(osr, osg, osd), ka, kd, ks, n, opacity, refraction);
                materials.push_back(mtl);
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
                Object* sphere = new Sphere(center, r, materials.back());
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
                if (ss.fail() || (c1 == 0 && c2 == 0 && c3 == 0)) {
                    std::cout << "Invalid input for attlight parameter. Must provide 8 floats 'attlight x y z w i c1 c2 c3'. Ensure c1 c2 c3 sum is > 0" << std::endl;
                    return -1;
                }
                Light* light = new AttenuationLight(Vector3(x, y, z), i, c1, c2 ,c3);
                lights.push_back(light);
            } else if (keyword.compare("v") == 0) {
                float x, y, z;
                ss >> x;
                ss >> y;
                ss >> z;
                if (ss.fail()) {
                    std::cout << "Invalid input for v parameter. Must provide 3 floats x y z" << std::endl;
                    return -1;
                }
                vertices.push_back(Vector3(x, y, z));
            } else if (keyword.compare("f") == 0) {
                std::string remainingData;
                remainingData = ss.str().substr(ss.tellg());
                
                std::smatch match;
                std::regex verticePoints("([0-9]+) ([0-9]+) ([0-9]+)"); // match flat-shaded triangle
                std::regex verticesAndNormals("([0-9]+)//([0-9]+) ([0-9]+)//([0-9]+) ([0-9]+)//([0-9]+)"); // match smooth-shaded triangle
                std::regex verticesAndTexture("([0-9]+)/([0-9]+) ([0-9]+)/([0-9]+) ([0-9]+)/([0-9]+)"); // match flat-shaded triangle with texture
                std::regex verticesAndTextureWithNormals("([0-9]+)/([0-9]+)/([0-9]+) ([0-9]+)/([0-9]+)/([0-9]+) ([0-9]+)/([0-9]+)/([0-9]+)"); // match smooth-shaded triangle with texture

                if (std::regex_search(remainingData, match, verticePoints)) {
                    int v1, v2, v3;
                    v1 = stoi(match[1]);
                    v2 = stoi(match[2]);
                    v3 = stoi(match[3]);
                    Object* triangle = new Triangle(vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1], materials.back());
                    objects.push_back(triangle);
                } else if (std::regex_search(remainingData, match, verticesAndNormals)) {
                    int v1, v2, v3, vn1, vn2, vn3;
                    v1 = stoi(match[1]);
                    vn1 = stoi(match[2]);
                    v2 = stoi(match[3]);
                    vn2 = stoi(match[4]);
                    v3 = stoi(match[5]);
                    vn3 = stoi(match[6]);
                    Object* triangle = new SmoothShadedTriangle(vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1], materials.back(),
                                                                normals[vn1 - 1], normals[vn2 - 1], normals[vn3 - 1]);
                    objects.push_back(triangle);
                } else if (std::regex_search(remainingData, match, verticesAndTexture)) {
                    int v1, v2, v3, vt1, vt2, vt3;
                    v1 = stoi(match[1]);
                    vt1 = stoi(match[2]);
                    v2 = stoi(match[3]);
                    vt2 = stoi(match[4]);
                    v3 = stoi(match[5]);
                    vt3 = stoi(match[6]);
                    Object* triangle = new Triangle(vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1],
                                                    materials.back(), textureCoords[vt1 - 1], textureCoords[vt2 - 1], textureCoords[vt3 - 1]);
                    objects.push_back(triangle);
                } else if (std::regex_search(remainingData, match, verticesAndTextureWithNormals)) {
                    int v1, v2, v3, vt1, vt2, vt3, vn1, vn2, vn3;
                    v1 = stoi(match[1]);
                    vt1 = stoi(match[2]);
                    vn1 = stoi(match[3]);
                    v2 = stoi(match[4]);
                    vt2 = stoi(match[5]);
                    vn2 = stoi(match[6]);
                    v3 = stoi(match[7]);
                    vt3 = stoi(match[8]);
                    vn3 = stoi(match[9]);
                    Object* triangle = new SmoothShadedTriangle(vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1], materials.back(),
                                                                textureCoords[vt1 - 1], textureCoords[vt2 - 1], textureCoords[vt3 - 1],
                                                                normals[vn1 - 1], normals[vn2 - 1], normals[vn3 - 1]);
                    objects.push_back(triangle);
                } else {
                    std::cout << "Invalid syntax for 'f' parameter" << std::endl;
                    return -1;
                }

            } else if (keyword.compare("vn") == 0) {
                float nx, ny, nz;
                ss >> nx;
                ss >> ny;
                ss >> nz;
                if (ss.fail()) {
                    std::cout << "Invalid input for vn parameter. Must provide 3 floats x y z" << std::endl;
                    return -1;
                }
                normals.push_back(Vector3(nx, ny, nz));
            } else if (keyword.compare("texture") == 0) {
                std::string ppmfile;
                ss >> ppmfile;

                if (ss.fail()) {
                    std::cout << "Invalid input for texture. Must provide file name" << std::endl;
                    return -1;
                }
                if (!utils::readTextureFile(ppmfile, materials)) {
                    return -1;
                }

            } else if (keyword.compare("vt") == 0) {
                float u, v;
                ss >> u;
                ss >> v;

                if (ss.fail()) {
                    std::cout << "Invalid input for vt. Must provide u v" << std::endl;
                    return -1;
                }

                textureCoords.push_back(Vector2(u, v));

            } else if (keyword.compare("softshadows") == 0) {
                int flag;
                ss >> flag;
                if (ss.fail()) {
                    std::cout << "Invalid input for softshadows flag. Must be 0 or 1" << std::endl;
                    return -1;
                }

                if (flag == 0) {
                    softShadowFlag = false;
                } else if (flag == 1) {
                    std::cout << "Using soft shadows. May take a while" << std::endl;
                    softShadowFlag = true;
                } else {
                    std::cout << "Invalid input for softshadows flag. Must be 0 or 1" << std::endl;
                    return -1;
                }
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

    // std::cout << "view aspect ratio: " << viewWidth / viewHeight << std::endl;
    // std::cout << "image aspect ratio: " << aspectRatio << std::endl;

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

Color Scene::traceRay(const Ray& ray) {
    int maxDepth = 10;
    // materialStack.clear(); // stores object materials so their refraction indexes can be accessed
    // materialStack.push_back(bkgcolor);
    Color color = recursiveTraceRay(ray, maxDepth, NULL, NULL, false);
    color.clamp();
    return color;
}

Color Scene::recursiveTraceRay(const Ray& ray, int maxDepth, const Object* originObject, const Vector3* originIntersection, bool insideObject) {
    if (maxDepth <= 0) {
        return Color(0.0f, 0.0f, 0.0f);
    }

    Object *closestObject = NULL;
    float minT = FLT_MAX;
    
    // iterate through objects in the scene and find the object whose interesection is closest, if any
    for (Object* object : objects) {
        float t = FLT_MAX;
        float maxT = t;
        float minDistance = 0.01f;

        // 
        if (object->rayIntersects(ray, t, maxT) && (!object->equals(*originObject) || (insideObject && dynamic_cast<Sphere*>(object)))) {
            if (t < minT && t > 0.0f) {
                minT = t;
                closestObject = object;

                Vector3 intersection = ray.getOrigin() + t * ray.getDir();
                if (originIntersection != NULL) {
                    // if intersection was really close to origin then ray should intersect at the further distance to the sphere
                    if (Vector3::distanceBetween(intersection, *originIntersection) < minDistance) {
                        minT = maxT;
                    }
                }
            }
        }
    }

    // get color of object if there was an intersection
    if (closestObject != NULL) {
        Vector3 intersectionPoint = ray.getOrigin() + minT * ray.getDir();

        Vector3 N = closestObject->calculateNormal(intersectionPoint);

        Color color = shadeRay(ray, *closestObject->getMaterial(), intersectionPoint, *closestObject);

        // If inside an object need to flip its normal direction
        if (insideObject) {
            N = -1.0f * N;
        }

        // std::cout << "rayIsInside: " << insideObject << " normal: " << N << std::endl;;


        Vector3 I = -1.0f * ray.getDir(); // Vector in opposite direction of the incident ray
        I.normalize();

        float NdotI = N.dot(I); // cosine of the angle of incidence

        Vector3 Rdir = 2.0f * NdotI * N - I; // reflected ray direction
        Rdir.normalize();

        Ray reflectedRay = Ray(intersectionPoint, Rdir);

        float nt = closestObject->getMaterial()->getRefractionIndex();
        float f0 = pow((nt - 1.0f) / (nt + 1.0f), 2.0f);
        float fr = f0 + (1.0f - f0) * pow(1.0f - NdotI, 5.0f); // fresnel reflectance coefficient
        float alpha = closestObject->getMaterial()->getOpacity();
        // float ni = materialStack.back().getRefractionIndex();

        Color reflectedColor;

        // object will reflect only when ks > 0
        if (closestObject->getMaterial()->getKs() > 0.0f) {
            reflectedColor = fr * recursiveTraceRay(reflectedRay, maxDepth - 1, closestObject, &intersectionPoint, insideObject);
        }
        // f0 = pow(((nt - ni) / (nt + ni)), 2.0f);
        // fr = f0 + (1.0f - f0) * pow(1.0f - NdotI, 5.0f); // fresnel reflectance coefficient

        float refractionRatio;
        if (insideObject) {
            refractionRatio = nt / bkgcolor.getRefractionIndex();
        } else {
            refractionRatio = bkgcolor.getRefractionIndex() / nt;
        }

        float sqrtQuantity = 1.0f - pow((refractionRatio), 2.0f) * (1.0f - pow(NdotI, 2.0f));

        Color refractedColor;

        // object will transmit ray if opacity < 1 and there is no total internal reflection
        if (alpha < 1.0f && sqrtQuantity >= 0) {

            Vector3 transmittedDir = (-1.0f * N) * sqrt(sqrtQuantity) + (refractionRatio) * ((NdotI) * N - I);
            transmittedDir.normalize();

            Ray refractedRay = Ray(intersectionPoint, transmittedDir);

            // if we are inside the object already and exiting use background refraction for the next refracted ray
            // if (insideObject) {
            //     materialStack.push_back(bkgcolor);
            // } else {
            //     materialStack.push_back(*closestObject->getMaterial());
            // }

            insideObject = !insideObject; // if object inside then will be outside. if object outside then will be inside
            refractedColor = (1.0f - fr) * (1.0f - alpha) * recursiveTraceRay(refractedRay, maxDepth - 1, closestObject, &intersectionPoint, insideObject);
        }

        return color + reflectedColor + refractedColor;
    }

    // no intersection so return the background color
    return bkgcolor.getDiffuseColor();
}

Color Scene::shadeRay(const Ray& ray, const Material& material, const Vector3& intersectionPoint, const Object& intersectedObject) const {
    Color colorResult;
    float ka = material.getKa();
    float kd = material.getKd();
    float ks = material.getKs();
    float n = material.getN();
    Color diffuseColor;
    Color specularColor = material.getSpecularColor();
    Color localIllumination(0.0f, 0.0f, 0.0f);
    int numberOfJitteredRays = 50;
    float jitterAmount = 0.01f;


    Vector3 L; // vector pointing towards light source
    Vector3 N; // surface normal
    Vector3 H; // direction halfway between light and direction towards the ray origin
    Vector3 V; // direction from intersection point to ray origin

    // Calculate the local illumination for each light
    for (Light *light : lights) {

        float shadowFlag = 0.0f;

        L = light->getDirToSource(intersectionPoint);
        L.normalize();

        // Check if point light (regular point light or attenuated) and softshadowflag is set to true. Do soft shadows in that case
        if (!dynamic_cast<DirectionalLight*>(light) && softShadowFlag) {
            for (int i = 0; i < numberOfJitteredRays; i++) {

                // Get a new jittered location from the original point light location
                Vector3 jitteredLocation = jitterLocation(light->getDirOrPoint(), jitterAmount);

                // Create a new light from the jittered position
                PointLight jitteredLight = PointLight(jitteredLocation, light->getIntensity());

                Vector3 dirToLight = jitteredLight.getDirOrPoint() - intersectionPoint;
                dirToLight.normalize();

                Ray shadowRay(intersectionPoint, dirToLight);
                shadowFlag += traceShadow(shadowRay, intersectedObject, jitteredLight);
            }
            // average the shadows
            shadowFlag = shadowFlag / numberOfJitteredRays;
        } else { // hard shadows 
            Ray shadowRay(intersectionPoint, L);
            shadowFlag = traceShadow(shadowRay, intersectedObject, *light);
        }

        // N = (intersectionPoint - intersectedObject.getCenter()) / intersectedObject.getRadius();
        // N.normalize();
        N = intersectedObject.calculateNormal(intersectionPoint);

        // if (flipNormal) {
        //     N = -1.0f * N;
        // }

        // V = ray.getOrigin() - intersectionPoint;
        V = -1.0f * ray.getDir();
        V.normalize();

        // H = (L + V) / 2.0f;
        H = (L + V);
        H.normalize();

        // H = (L + I);
        // H.normalize();

        // calculate diffuse color for the object
        diffuseColor = intersectedObject.calculateColor(intersectionPoint);

        localIllumination = localIllumination + (shadowFlag * (kd * diffuseColor * std::max(0.0f, (N.dot(L))) + ks * specularColor * pow(std::max(0.0f, (N.dot(H))), n)));


        if (AttenuationLight* attLight = dynamic_cast<AttenuationLight*>(light)) {
            float distance = Vector3::distanceBetween(intersectionPoint, light->getDirOrPoint());
            float att = attLight->attenuation(distance);
            localIllumination = localIllumination * att;
        }
    }

    // add in the ambient component
    colorResult = ka * diffuseColor + localIllumination;

    // Apply depthcueing to the illumination
    if (depthCueingFlag)
    {
        float distance = Vector3::distanceBetween(eye, intersectionPoint);
        colorResult = depthCue.applyDepthCueing(colorResult, distance);
    }

    // clamp color between 0.0f and 1.0f
    colorResult.clamp();

    return colorResult;
}

float Scene::traceShadow(const Ray& ray, const Object& originObject, Light& light) const {
    float shadowFlag = 1.0f;

    // iterate through objects in the scene and find the object whose interesection is closest, if any
    for (Object *object : objects) {
        float t = FLT_MAX;
        float _ = 0.0f;

        if (!object->equals(originObject)) { // don't check the object where the shadow ray originates

            if (object->rayIntersects(ray, t, _)) {

                if (t > 0.0f) { // ray intersects sphere
                    if (dynamic_cast<DirectionalLight *>(&light)) {
                        shadowFlag = shadowFlag * (1.0f - object->getMaterial()->getOpacity());
                    } else {
                        float distance = Vector3::distanceBetween(ray.getOrigin(), light.getDirOrPoint());

                        if (t > distance) { // object is behind point light
                            shadowFlag = 1.0f;
                        } else {
                            shadowFlag = shadowFlag * (1.0f - object->getMaterial()->getOpacity());
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

    std::ostream &operator<<(std::ostream &out, const Scene &scene) {
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
        for (Object *object : scene.objects)
        {
            object->printInfo();
        }
        for (Light *light : scene.lights)
        {
            // out << *light << std::endl;
            light->printInfo();
        }
        return out;
    }
