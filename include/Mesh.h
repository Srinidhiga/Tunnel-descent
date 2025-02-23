#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    // Mesh Data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // Constructors
    Mesh(); // Default constructor
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
    
    // Destructor
    ~Mesh();

    // Function to draw the mesh
    void Draw(GLuint shaderProgram);

private:
    // Render data
    GLuint VAO, VBO, EBO;
    
    // Initializes all the buffer objects/arrays
    void setupMesh();
};

#endif // MESH_H
