#pragma once
#include "Color.h"
#include <ostream>

class Material {
    private:
        Color diffuseColor;
        Color specularColor;
        float ka; // ambient
        float kd; // diffuse
        float ks; // specular
        float n; // intensity

    public:
        Material();

        /**
         * constructor for material
         * 
         * @param diffuseColor_ the diffuse color
         * @param specularColor_ the specular color
         * @param ka_ the ambient scalar
         * @param kd_ the diffuse scalar
         * @param ks_ the specular scalar
         * @param n_ the magnitude of specular highlight intensity
         */
        Material(const Color& diffuseColor_, const Color& specularColor_, float ka_, float kd_, float ks_, float n_);

        const Color& getDiffuseColor() const { return diffuseColor; } 
        const Color& getSpecularColor() const { return specularColor; }
        const float getKa() const { return ka; }
        const float getKd() const { return kd; }
        const float getKs() const { return ks; }
        const float getN() const { return n; }

        /**
         * Overload the out stream operator to print a vector3
         *
         * @param out the outstream
         * @param material the material object whose fields are printed
         */
        friend std::ostream& operator<<(std::ostream& out, const Material& material);

};