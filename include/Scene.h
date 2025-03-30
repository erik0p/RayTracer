#pragma once
#include <vector>
#include <ostream>
#include "Vector3.h"
#include "Vector2.h"
#include "Material.h"
#include "Object.h"
#include "Sphere.h"
#include "Ray.h"
#include "Light.h"
#include "DepthCueing.h"

class Scene {
    private:
        Vector3 eye;
        Vector3 viewdir;
        Vector3 updir;

        float vfov;
        float imgWidth;
        float imgHeight;

        // Color bkgcolor;
        Material bkgcolor;
        // Color mtlcolor;
        Material mtlcolor;
        std::vector<Object*> objects;
        std::vector<Light*> lights;

        DepthCueing depthCue;
        bool depthCueingFlag;



        Vector3 ul;
        Vector3 ur;
        Vector3 ll;
        Vector3 lr;

        Vector3 v;
        Vector3 u;

        float viewHeight;
        float viewWidth;

        std::vector<Vector3> vertices;
        std::vector<Vector3> normals;
        std::vector<Vector2> textureCoords;

        bool softShadowFlag;
       
    public:
        Scene();
        ~Scene();

        const Vector3& getEye() const { return eye; }
        const Vector3& getViewdir() const { return viewdir; }
        const Vector3& getUpdir() const { return updir; }
        const float& getVfov() const { return vfov; }
        const float& getImgWidth() const { return imgWidth; }
        const float& getImgHeight() const { return imgHeight; }
        // const Color& getBkgcolor() const { return bkgcolor; }
        const Material& getBkgcolor() const { return bkgcolor; }
        const Material& getMtlcolor() const { return mtlcolor; }
        const std::vector<Object*> getObjects() const { return objects; }
        const Vector3& getUl() const { return ul; }
        const Vector3& getUr() const { return ur; }
        const Vector3& getLl() const { return ll; }
        const Vector3& getLr() const { return lr; }
        const Vector3& getV() const { return v; }
        const Vector3& getU() const { return u; }
        const std::vector<Light*> getLights() const { return lights; }
        const float& getViewHeight() const { return viewHeight; }
        const float& getViewWidth() const { return viewWidth; }
        const std::vector<Vector3> getVertices() const { return vertices; }
        const std::vector<Vector3> getNormals() const { return normals; }
        const std::vector<Vector2> getTextureCoords() const { return textureCoords; }
        const bool getSoftShadowFlag() const { return softShadowFlag; }


        /**
         * reads in a file and intializes the fields using data from the file
         *
         * @param fileName name of the file to read
         * 
         * @return 0 if successfully read file and -1 if unsuccessful
         */
        int initializeScene(std::string fileName);

        /**
         * traces a ray from its origin to a point in the view window and determines the color of the pixel hit by the ray
         *
         * @param ray the ray to trace
         * 
         * @return the color of the pixel hit by the ray
         */
        Color traceRay(const Ray& ray) const;

        Color recursiveTraceRay(const Ray& ray, int depth, const Object* originObject) const;

        /**
         * converts a row and col in an image to a 3d location in the view space
         *
         * @param row the row of the image
         * @param col the col of the image
         * 
         * @return a vector representing the position in view space from the pixels row col
         */
        Vector3 imageToView(int row, int col) const;

        /**
         * shades a ray using the Blinn-Phong model
         *
         * @param ray the ray to shade
         * @param intersectionPoint the point where the ray intersects the object
         * @param intersectedObject the object intersected by the ray
         * 
         * @return the illuminated at the interesected point
         */
        Color shadeRay(const Ray& ray,const Vector3& intersectionPoint, const Object& intersectedObject) const;

        /**
         * traces a shadow to test if it interesects an object
         *
         * @param ray the ray to trace
         * @param originObject the object where the ray originates from
         * @param light the light source to trace towards
         * 
         * @return a shadow flag where 0.0f is an intersection and 1.0f is no intersection
         */
        float traceShadow(const Ray& ray, const Object& originObject, Light& light) const;

        /**
         * jitters a location by a specified amount
         *
         * @param location the location to jitter
         * @param jitterAmount the amount to jitter the location by
         * 
         * @return a location that has been randomly jittered
         */
        Vector3 jitterLocation(const Vector3& location, float jitterAmount) const;

        /**
         * Overload the out stream operator to print a scene
         *
         * @param out the outstream
         * @param scene the scene whose fields are printed
         */
        friend std::ostream& operator<<(std::ostream& out, const Scene& scene);
};
