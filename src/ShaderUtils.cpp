#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string ReadShaderFromFile(const char* shaderFilePath) {
    std::ifstream shaderFile(shaderFilePath);
    if (!shaderFile.is_open()) {
        std::cerr << "Failed to open shader file: " << shaderFilePath << std::endl;
        return "";
    }
    std::stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    shaderFile.close();
    return shaderStream.str();
}

GLuint CompileShader(const char* source, GLenum shaderType) {
    GLuint shaderID = glCreateShader(shaderType);
    glShaderSource(shaderID, 1, &source, NULL);
    glCompileShader(shaderID);

    GLint result = GL_FALSE;
    int infoLogLength;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> shaderErrorMessage(infoLogLength);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
        std::cerr << "Shader compilation error: " << &shaderErrorMessage[0] << std::endl;
        glDeleteShader(shaderID);
        return 0;
    }
    return shaderID;
}

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {
    std::string VertexShaderCode = ReadShaderFromFile(vertex_file_path);
    std::string FragmentShaderCode = ReadShaderFromFile(fragment_file_path);

    GLuint VertexShaderID = CompileShader(VertexShaderCode.c_str(), GL_VERTEX_SHADER);
    if (VertexShaderID == 0) return 0; 

    GLuint FragmentShaderID = CompileShader(FragmentShaderCode.c_str(), GL_FRAGMENT_SHADER);
    if (FragmentShaderID == 0) {
        glDeleteShader(VertexShaderID);
        return 0;  
    }

    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    GLint result = GL_FALSE;
    int infoLogLength;
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {
        glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> programErrorMessage(std::max(infoLogLength, int(1)));
        glGetProgramInfoLog(ProgramID, infoLogLength, NULL, &programErrorMessage[0]);
        std::cerr << "Shader linking error: " << &programErrorMessage[0] << std::endl;
        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);
        glDeleteProgram(ProgramID);
        return 0;
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}
