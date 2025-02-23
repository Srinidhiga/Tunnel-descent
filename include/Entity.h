#ifndef ENTITY_H
#define ENTITY_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Mesh.h"

class Entity {
public:
    Entity(const Mesh& meshData);
    ~Entity();
    void Draw(GLuint shaderProgram); 

private:
    GLuint VAO, VBO, EBO;
    size_t vertexCount; 

    void setupMesh(const Mesh& meshData);
};

#endif // ENTITY_H
