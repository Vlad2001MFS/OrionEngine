#include "Material.h"

namespace oe {

Material::Material(const glm::vec3 & ambient, const glm::vec3 & diffuse, const glm::vec3 & specular, float specularPower)
    : mAmbient(ambient), mDiffuse(diffuse), mSpecular(specular), mSpecularPower(specularPower) { }

Material::~Material() { }

const glm::vec3 & Material::GetAmbient() const {
    return mAmbient;
}

const glm::vec3 & Material::GetDiffuse() const {
    return mDiffuse;
}

const glm::vec3 & Material::GetSpecular() const {
    return mSpecular;
}

float Material::GetSpecularPower() const {
    return mSpecularPower;
}

}