#pragma once
#include <vector>
#include <ostream>
#include "Vector3.h"
#include "Material.h"
#include "Sphere.h"
#include "Ray.h"
#include "Light.h"

class Scene {
    private:
        Vector3 eye;
        Vector3 viewdir;
        Vector3 updir;

        float vfov;
        float imgWidth;
        float imgHeight;

        Color bkgcolor;
        // Color mtlcolor;
        Material mtlcolor;
        std::vector<Sphere*> objects;
        std::vector<Light*> lights;

        Vector3 ul;
        Vector3 ur;
        Vector3 ll;
        Vector3 lr;

        Vector3 v;
        Vector3 u;

        float viewHeight;
        float viewWidth;
       
    public:
        Scene();
        ~Scene();

        const Vector3& getEye() const { return eye; }
        const Vector3& getViewdir() const { return viewdir; }
        const Vector3& getUpdir() const { return updir; }
        const float& getVfov() const { return vfov; }
        const float& getImgWidth() const { return imgWidth; }
        const float& getImgHeight() const { return imgHeight; }
        const Color& getBkgcolor() const { return bkgcolor; }
        const Material& getMtlcolor() const { return mtlcolor; }
        const std::vector<Sphere*> getSpheres() const { return objects; }
        const Vector3& getUl() const { return ul; }
        const Vector3& getUr() const { return ur; }
        const Vector3& getLl() const { return ll; }
        const Vector3& getLr() const { return lr; }
        const Vector3& getV() const { return v; }
        const Vector3& getU() const { return u; }
        const std::vector<Light*> getLights() const { return lights; }
        const float& getViewHeight() const { return viewHeight; }
        const float& getViewWidth() const { return viewWidth; }

        /*
         * reads in a file and intializes the fields using data from the file
         *
         * @param fileName name of the file to read
         * 
         * @return 0 if successfully read file and -1 if unsuccessful
         */
        int initializeScene(std::string fileName);

        /*
         * traces a ray from its origin to a point in the view window and determines the color of the pixel hit by the ray
         *
         * @param ray the ray to trace
         * 
         * @return the color of the pixel hit by the ray
         */
        Color traceRay(const Ray& ray) const;

        /*
         * converts a row and col in an image to a 3d location in the view space
         *
         * @param row the row of the image
         * @param col the col of the image
         * 
         * @return a vector representing the position in view space from the pixels row col
         */
        Vector3 imageToView(int row, int col) const;

        /*
         * Overload the out stream operator to print a scene
         *
         * @param out the outstream
         * @param scene the scene whose fields are printed
         */

        Color shadeRay(const Ray& ray, const Material& material, const Vector3& intersectionPoint, const Sphere& intersectedSphere) const;
        float traceShadow(const Ray& ray, const Sphere& originSphere, const Light& light) const;
        friend std::ostream& operator<<(std::ostream& out, const Scene& scene);
};
