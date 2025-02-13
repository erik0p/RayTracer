#pragma once
#include <vector>
#include <ostream>
#include "Vector3.h"
#include "Color.h"
#include "Object.h"
#include "Ray.h"

class Scene {
    private:
        Vector3 eye;
        Vector3 viewdir;
        Vector3 updir;

        float vfov;
        float imgWidth;
        float imgHeight;

        Color bkgcolor;
        Color mtlcolor;
        std::vector<Object*> objects;

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
        const Color& getMtlcolor() const { return mtlcolor; }
        const std::vector<Object*> getSpheres() const { return objects; }
        const Vector3& getUl() const { return ul; }
        const Vector3& getUr() const { return ur; }
        const Vector3& getLl() const { return ll; }
        const Vector3& getLr() const { return lr; }
        const Vector3& getV() const { return v; }
        const Vector3& getU() const { return u; }
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
        Vector3 imageToView(int row, int col);

        /*
         * Overload the out stream operator to print a scene
         *
         * @param out the outstream
         * @param scene the scene whose fields are printed
         */
        friend std::ostream& operator<<(std::ostream& out, const Scene& scene);
};
