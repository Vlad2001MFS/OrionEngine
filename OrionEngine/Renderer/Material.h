#pragma once
#include "glm/glm.hpp"
#include <string>

namespace oe {

class Material {
public:
    Material(const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float specularPower);
    ~Material();

    const glm::vec3 &GetAmbient() const;
    const glm::vec3 &GetDiffuse() const;
    const glm::vec3 &GetSpecular() const;
    float GetSpecularPower() const;

private:
    __declspec(align(16)) glm::vec3 mAmbient, mDiffuse, mSpecular;
    __declspec(align(4)) float mSpecularPower;
};

}