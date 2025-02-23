#include "SceneLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

void SceneLoader::loadLights(const std::string& filepath) {
    std::ifstream file(filepath);
    std::string line;
    while (std::getline(file, line)) {
        glm::vec3 pos = parseVec3(line);
        lights.emplace_back(pos);
    }
    file.close();
}

void SceneLoader::loadBezierCurve(const std::string& filepath) {
    std::ifstream file(filepath);
    std::string line;
    while (std::getline(file, line)) {
        if (line[0] == 'p' || line[0] == 'c') {
            bezierPoints.push_back(parseVec3(line.substr(2)));
        }
    }
    file.close();
}

std::vector<PointLight> SceneLoader::getLights() const {
    return lights;
}

std::vector<glm::vec3> SceneLoader::getBezierPoints() const {
    return bezierPoints;
}

glm::vec3 SceneLoader::parseVec3(const std::string& line) {
    std::istringstream iss(line);
    float x, y, z;
    iss >> x >> y >> z;
    return glm::vec3(x, y, z);
}
