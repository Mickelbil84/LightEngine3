#pragma once

#include "le3_engine_systems.h"

namespace le3 {
    class LE3EditorComAddShader : public LE3EditorCommand { 
    public:
        LE3EditorComAddShader(std::string name, std::string vertexPath, std::string fragmentPath);

        virtual void execute();
        virtual void undo();

    private:
        std::string m_name, m_vertexPath, m_fragmentPath;
    };
}