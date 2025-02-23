#include "PointLight.h"

PointLight::PointLight(const glm::vec3& pos) : position(pos) {
}

glm::vec3 PointLight::getPosition() const {
    return position;
}
