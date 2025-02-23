#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Camera {
public:
    Camera();

    void update(float t);
    glm::mat4 getViewMatrix() const;

    
    void setBezierPoints(const std::vector<glm::vec3>& points);

private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    std::vector<glm::vec3> bezierPoints;

   
    glm::vec3 computeBezierPoint(float t);

};

#endif // CAMERA_H
