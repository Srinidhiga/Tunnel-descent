#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <glm/glm.hpp>

class PointLight {
public:
    PointLight(const glm::vec3& pos);

    glm::vec3 getPosition() const;

private:
    glm::vec3 position;

   
};

#endif // POINT_LIGHT_H
