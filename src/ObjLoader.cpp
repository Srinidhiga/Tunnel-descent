#include "ObjLoader.h"
#include "tiny_obj_loader.h"
#include <iostream> 

bool ObjLoader::LoadObj(const std::string& filename, Mesh& mesh) {
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;  
    std::vector<tinyobj::material_t> materials;  
    std::string warn, err;

    std::string base_dir = filename.substr(0, filename.find_last_of("/\\") + 1);

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str(), base_dir.c_str(), true, true);

    if (!warn.empty()) {
        std::cout << "Warning: " << warn << std::endl;
    }

    if (!err.empty()) {
        std::cerr << "Error: " << err << std::endl;
        return false;
    }

    if (!ret) {
        std::cerr << "Failed to load/parse .obj file." << std::endl;
        return false;
    }

    for (const auto& shape : shapes) {
        size_t index_offset = 0;
        for (size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++) {
            int fv = shape.mesh.num_face_vertices[f];

            for (size_t v = 0; v < fv; v++) {
                tinyobj::index_t idx = shape.mesh.indices[index_offset + v];

                Vertex vertex;

                // Position
                vertex.Position = glm::vec3(
                    attrib.vertices[3 * idx.vertex_index + 0],
                    attrib.vertices[3 * idx.vertex_index + 1],
                    attrib.vertices[3 * idx.vertex_index + 2]
                );

                // Normal
                if (idx.normal_index >= 0) {
                    vertex.Normal = glm::vec3(
                        attrib.normals[3 * idx.normal_index + 0],
                        attrib.normals[3 * idx.normal_index + 1],
                        attrib.normals[3 * idx.normal_index + 2]
                    );
                } else {
                    vertex.Normal = glm::vec3(0, 0, 0); 
                }

                // Texture coordinates
                if (idx.texcoord_index >= 0) {
                    vertex.TexCoords = glm::vec2(
                        attrib.texcoords[2 * idx.texcoord_index + 0],
                        attrib.texcoords[2 * idx.texcoord_index + 1]
                    );
                } else {
                    vertex.TexCoords = glm::vec2(0, 0);
                }

                // Add vertex to mesh
                mesh.vertices.push_back(vertex);
            }
            index_offset += fv;
        }
    }

    return true;
}
