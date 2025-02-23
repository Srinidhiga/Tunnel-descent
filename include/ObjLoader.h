#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H
#include "Mesh.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>


class ObjLoader {
public:
    static bool LoadObj(const std::string& filename, Mesh& mesh);
};

#endif // OBJ_LOADER_H
