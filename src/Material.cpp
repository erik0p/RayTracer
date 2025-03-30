#include "Material.h"
#include <ostream>
#include <fstream>
#include <sstream>
#include <vector>

Material::Material() {
    diffuseColor = Color();
    specularColor = Color();
}

Material::Material(const Color& diffuseColor_, const Color& specularColor_, 
    float ka_, float kd_, float ks_, float n_, float opacity_, float refractionIndex_) {
    diffuseColor = diffuseColor_;
    specularColor = specularColor_;
    ka = ka_;
    kd = kd_;
    ks = ks_;
    n = n_;
    opacity = opacity_;
    refractionIndex = refractionIndex_;
    textureHeight = 0;
    textureWidth = 0;
    textureFlag = false;
}

Material::Material(float ka_, float kd_, float ks_, float n_, float opacity_, float refractionIndex_, const Color& specularColor_, 
    int textureWidth_, int textureHeight_, std::vector<std::vector<Color>> texture_) {
    ka = ka_;
    kd = kd_;
    ks = ks_;
    n = n_;
    opacity = opacity_;
    refractionIndex = refractionIndex_;
    specularColor = specularColor_;
    textureFlag = true;
    textureWidth = textureWidth_;
    textureHeight = textureHeight_;
    texture = texture_;
}

Color Material::lookupColor(int i, int j) const {
    if (textureFlag) {
        return texture[i][j];
    }
    // if this is called on a material without a texture return the diffuse color
    return diffuseColor;
}

std::ostream& operator<<(std::ostream& out, const Material& material) {
    out << "diffuse color: " << material.getDiffuseColor() << std::endl
        << "specular color: " << material.getSpecularColor() << std::endl
        << "ka: " << material.getKa()
        << " kd: " << material.getKd()
        << " ks: " << material.getKs()
        << " n: " << material.getN() << std::endl
        << "refraction: " << material.getRefractionIndex() 
        << "opacity: " << material.getOpacity()
        << " texture: " << "width: " << material.getTextureWidth()
        << " height: " << material.getTextureHeight();

    return out;
}