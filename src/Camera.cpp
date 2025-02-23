#include "Camera.h"

Camera::Camera() : position(glm::vec3(0.0f, 0.0f, 0.0f)), front(glm::vec3(0.0f, 0.0f, -1.0f)), up(glm::vec3(0.0f, 1.0f, 0.0f)) {
}

void Camera::setBezierPoints(const std::vector<glm::vec3>& points) {
    bezierPoints = points;
}

void Camera::update(float t) {
    position = computeBezierPoint(t);
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::computeBezierPoint(float t) {
    // Bezier curve equation for cubic Bezier
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    glm::vec3 p = uuu * bezierPoints[0]; // first term
    p += 3 * uu * t * bezierPoints[1]; // second term
    p += 3 * u * tt * bezierPoints[2]; // third term
    p += ttt * bezierPoints[3]; // fourth term

    return p;
}
