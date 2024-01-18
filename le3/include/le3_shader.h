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

        inline void uniform(std::string uniformName, glm::vec3 v);
        inline void uniform(std::string uniformName, glm::vec4 v);
        inline void uniform(std::string uniformName, glm::mat4 m);
        inline void uniform(std::string uniformName, unsigned int i);
        inline void uniform(std::string uniformName, float x);

    private:
        unsigned int m_program;
        std::map<std::string, int> m_uniformLocation;

        // Helper methods
        unsigned int compileShaderFromSource(std::string shaderSource, int type);
        inline int getUniformLocation(std::string uniformName);
    };
    using LE3ShaderPtr = std::shared_ptr<LE3Shader>;
}