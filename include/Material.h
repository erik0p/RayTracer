#pragma once
#include "Color.h"
#include <ostream>
#include <vector>

class Material {
    private:
        Color diffuseColor;
        Color specularColor;
        float ka; // ambient
        float kd; // diffuse
        float ks; // specular
        float n; // intensity
        bool textureFlag;
        int textureHeight;
        int textureWidth;
        std::vector<std::vector<Color>> texture;

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

        /**
         * constructor for material when using as a texture
         * 
         * @param ka_ the ambient scalar
         * @param kd_ the diffuse scalar
         * @param ks_ the specular scalar
         * @param n_ the magnitude of specular highlight intensity
         * @param specularColor_ the specular color
         * @param textureWidth_ width of the texture
         * @param textureHeight_ height of the texture
         * @param texture_ 2d array to store the texture colors
         */
        Material(float ka_, float kd_, float ks_, float n_, const Color& specularColor_, 
            int textureWidth_, int textureHeight_, std::vector<std::vector<Color>> texture_);

        const Color& getDiffuseColor() const { return diffuseColor; } 
        const Color& getSpecularColor() const { return specularColor; }
        const float getKa() const { return ka; }
        const float getKd() const { return kd; }
        const float getKs() const { return ks; }
        const float getN() const { return n; }
        const bool getTextureFlag() const { return textureFlag; }
        const int getTextureWidth() const { return textureWidth; }
        const int getTextureHeight() const { return textureHeight; }
        const std::vector<std::vector<Color>> getTexture() const { return texture; }

        /**
         * @param i row index into the 2d texture
         * @param j col index into the 2d texture
         * 
         * @return the color at [i][j] in the texture
         */
        Color lookupColor(int i, int j) const;

        /**
         * Overload the out stream operator to print a vector3
         *
         * @param out the outstream
         * @param material the material object whose fields are printed
         */
        friend std::ostream& operator<<(std::ostream& out, const Material& material);

};