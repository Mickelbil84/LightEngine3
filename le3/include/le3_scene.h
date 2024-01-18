#pragma once

#include <map>
#include <string>

#include "le3_shader.h"

namespace le3 {
    class LE3Scene {
    public:
        void addShaderFromFile(std::string name, std::string vertexShaderPath, std::string fragmentShaderPath);
        void addShaderFromSource(std::string name, std::string vertexShaderSource, std::string fragmentShaderSource);

        inline LE3ShaderPtr getShader(std::string name) { return m_pShaders[name]; }

    private:
        std::map<std::string, LE3ShaderPtr> m_pShaders;

        // Helper methods
        std::string readFile(std::string filename);
    };
}