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
    void CompileShaderFromSource(std::string vertexShaderSource, std::string fragmentShaderSource);

    // Activates the shader
    void Use();
    // Deletes the shader
    void Delete();

    void Uniform(std::string uniformName, glm::vec3 v);
    void Uniform(std::string uniformName, glm::vec4 v);
    void Uniform(std::string uniformName, glm::mat4 m);
    void Uniform(std::string uniformName, GLuint i);

    std::string m_vertexShaderPath, m_fragmentShaderPath;

    void SetName(std::string name);
    std::string GetName() const;

private:
    // Reads shader file into an `std::string`
    static std::string ReadShaderFile(std::string filePath);
    
    // Creates and compiles a shader of a given type. 
    // Prints verbosely any errors that may occur in DEBUG builds.
    GLuint CreateShader(std::string shaderSourceString, std::string filePath, GLenum type);
    
    // Returns the given uniform's location
    GLint GetUniformLocation(std::string uniformName);

    GLuint m_program;
    std::map<std::string, GLint> m_uniformLocation;
    std::string m_name;
};