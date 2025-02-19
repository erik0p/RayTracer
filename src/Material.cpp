#include "Material.h"
#include <ostream>

Material::Material() {
    diffuseColor = Color();
    specularColor = Color();
}

Material::Material(const Color& diffuseColor_, const Color& specularColor_, 
    float ka_, float kd_, float ks_, float n_) {
    diffuseColor = diffuseColor_;
    specularColor = specularColor_;
    ka = ka_;
    kd = kd_;
    ks = ks_;
    n = n_;
}

std::ostream& operator<<(std::ostream& out, const Material& material) {
    out << "diffuse color: " << material.getDiffuseColor() << std::endl
        << "specular color: " << material.getSpecularColor() << std::endl
        << "ka: " << material.getKa()
        << " kd: " << material.getKd()
        << " ks: " << material.getKs()
        << " n: " << material.getN();

    return out;
}