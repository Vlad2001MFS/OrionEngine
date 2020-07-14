#pragma once
#include "glm/glm.hpp"

namespace oe {

enum class LightType : int {
    Dir,
    Point,
    Spot
};

struct Light {
    Light();

    static Light CreateDirLight(const glm::vec3 &direction, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular);
    static Light CreatePointLight(const glm::vec3 &position, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
                                  const glm::vec3 &attenuation);
    static Light CreateSpotLight(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &ambient, const glm::vec3 &diffuse,
                                 const glm::vec3 &specular, const glm::vec3 &attenuation, const glm::vec2 &spotAngles);

    __declspec(align(16)) glm::vec3 position, direction;
    __declspec(align(16)) glm::vec3 ambient, diffuse, specular;
    __declspec(align(16)) glm::vec3 attenuation;
    __declspec(align(8)) glm::vec2 spotAngles;
    __declspec(align(4)) LightType type;
};

}