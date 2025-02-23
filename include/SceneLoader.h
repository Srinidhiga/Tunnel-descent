#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H

#include <string>
#include <vector>
#include "Camera.h"
#include "PointLight.h"

class SceneLoader {
public:
    void loadObj(const std::string& filepath);
    void loadLights(const std::string& filepath);
    void loadBezierCurve(const std::string& filepath);

    std::vector<PointLight> getLights() const;
    std::vector<glm::vec3> getBezierPoints() const;

private:
    std::vector<PointLight> lights;
    std::vector<glm::vec3> bezierPoints;

    glm::vec3 parseVec3(const std::string& line);
};

#endif // SCENE_LOADER_H
