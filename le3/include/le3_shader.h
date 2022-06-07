#pragma once
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <gl/glew.h>

#define SHADER_ERROR_BUFFER_SIZE 2048

// Shader class that supports GLSL programs
// Also allow for uniform updates
class LE3Shader
{
public:
    LE3Shader();

    // Compiles the shader given source files. Vertex and fragment shaders are mandatory.
    void CompileShader(std::string vertexShaderPath, std::string fragmentShaderPath);

    // Activates the shader
    void Use();
    // Deletes the shader
    void Delete();

    void Uniform(std::string uniformName, glm::vec4 v);
    void Uniform(std::string uniformName, glm::mat4 m);


private:
    // Reads shader file into an `std::string`
    static std::string ReadShaderFile(std::string filePath);
    
    // Creates and compiles a sahder of a given type. 
    // Prints verbosely any errors that may ocurr in DEBUG builds.
    GLuint CreateShader(std::string filePath, GLenum type);
    
    // Returns the given uniform's location
    GLint GetUniformLocation(std::string uniformName);

    GLuint m_program;
    std::map<std::string, GLint> m_uniformLocation;
};