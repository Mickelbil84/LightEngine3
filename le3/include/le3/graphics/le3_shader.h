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

        void uniform(std::string uniformName, glm::vec2 v);
        void uniform(std::string uniformName, glm::vec3 v);
        void uniform(std::string uniformName, glm::vec4 v);
        void uniform(std::string uniformName, glm::mat4 m);
        void uniform(std::string uniformName, unsigned int i);
        void uniform(std::string uniformName, float x);

        int key() const { return m_program * 2 + 1; } // Some unique key for the shader

        void setName(std::string name) { m_name = name; }
        std::string getName() const { return m_name; }

        std::pair<bool, std::string> recompile(std::string vertexShaderSource, std::string fragmentShaderSource);
        void recompile();

        bool isOk() const { return m_shaderOk; }
        std::string getErrorMessage() const { return m_errorMessage; }

    private:
        std::string m_name;
        unsigned int m_program;
        std::map<std::string, int> m_uniformLocation;
        bool m_shaderOk = true;
        std::string m_errorMessage = "";

        // Helper methods
        unsigned int compileShaderFromSource(std::string shaderSource, int type, bool& success, std::string& error);
        inline int getUniformLocation(std::string uniformName);
        void recompileToErrorShader();
    };
    using LE3ShaderPtr = std::weak_ptr<LE3Shader>;
}