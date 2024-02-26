#pragma once

#include <map>
#include <memory>
#include <string>
#include <stdexcept>

#include <glm/glm.hpp>

namespace le3 {
    class LE3Shader {
    public:
        LE3Shader(std::string vertexShaderSource, std::string fragmentShaderSource);
        ~LE3Shader();

        void use() const;

        void uniform(std::string uniformName, glm::vec3 v);
        void uniform(std::string uniformName, glm::vec4 v);
        void uniform(std::string uniformName, glm::mat4 m);
        void uniform(std::string uniformName, unsigned int i);
        void uniform(std::string uniformName, float x);

        int key() const { return m_program * 2 + 1; } // Some unique key for the shader

    private:
        unsigned int m_program;
        std::map<std::string, int> m_uniformLocation;

        // Helper methods
        unsigned int compileShaderFromSource(std::string shaderSource, int type);
        inline int getUniformLocation(std::string uniformName);
    };
    using LE3ShaderPtr = std::shared_ptr<LE3Shader>;
}