#include "Light.h"

namespace oe {

Light::Light()
    : type(LightType::Dir), position(0, 0, 0), direction(0, 0, 0), ambient(0, 0, 0), diffuse(0, 0, 0), specular(0, 0, 0),
    attenuation(0, 0, 0), spotAngles(0, 0) { }

Light Light::CreateDirLight(const glm::vec3 & direction, const glm::vec3 & ambient, const glm::vec3 & diffuse, const glm::vec3 & specular) {
    Light light;
    light.type = LightType::Dir;
    light.direction = direction;
    light.ambient = ambient;
    light.diffuse = diffuse;
    light.specular = specular;
    return light;
}

Light Light::CreatePointLight(const glm::vec3 & position, const glm::vec3 & ambient, const glm::vec3 & diffuse, const glm::vec3 & specular,
                              const glm::vec3 & attenuation) {
    Light light;
    light.type = LightType::Point;
    light.position = position;
    light.ambient = ambient;
    light.diffuse = diffuse;
    light.specular = specular;
    light.attenuation = attenuation;
    return light;
}

Light Light::CreateSpotLight(const glm::vec3 & position, const glm::vec3 & direction, const glm::vec3 & ambient, const glm::vec3 & diffuse,
                             const glm::vec3 & specular, const glm::vec3 & attenuation, const glm::vec2 & spotAngles) {
    Light light;
    light.type = LightType::Spot;
    light.position = position;
    light.direction = direction;
    light.ambient = ambient;
    light.diffuse = diffuse;
    light.specular = specular;
    light.attenuation = attenuation;
    light.spotAngles = spotAngles;
    return light;
}

}