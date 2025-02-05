#pragma once
#include <vector>
#include <ostream>
#include "Vector3.h"
#include "Color.h"
#include "Sphere.h"
#include "Ray.h"

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

        Vector3 ul;
        Vector3 ur;
        Vector3 ll;
        Vector3 lr;

        Vector3 v;
        Vector3 u;

        float viewHeight;
        float viewWidth;
       
    public:
        SceneReader();

        const Vector3& getEye() const { return eye; }
        const Vector3& getViewdir() const { return viewdir; }
        const Vector3& getUpdir() const { return updir; }
        const float& getVfov() const { return vfov; }
        const int& getWidth() const { return width; }
        const int& getHeight() const { return height; }
        const Color& getBkgcolor() const { return bkgcolor; }
        const Color& getMtlcolor() const { return mtlcolor; }
        const std::vector<Sphere> getSpheres() const { return spheres; }
        const Vector3& getUl() const { return ul; }
        const Vector3& getUr() const { return ur; }
        const Vector3& getLl() const { return ll; }
        const Vector3& getLr() const { return lr; }
        const Vector3& getV() const { return v; }
        const Vector3& getU() const { return u; }
        const float& getViewHeight() const { return viewHeight; }
        const float& getViewWidth() const { return viewWidth; }

        int initializeScene(std::string fileName);
        Color traceRay(const Ray& ray) const;
        Vector3 imageToView(int row, int col);
        friend std::ostream& operator<<(std::ostream& out, const SceneReader& sceneReader);
};
