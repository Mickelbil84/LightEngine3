#pragma once

#include "core/le3_engine_systems.h"

namespace le3 {
    class LE3EditorComDeleteShader : public LE3EditorCommand { 
    public:
        LE3EditorComDeleteShader(std::string name, std::string vertexPath, std::string fragmentPath);

        virtual void execute();
        virtual void undo();

    private:
        std::string m_name, m_vertexPath, m_fragmentPath;
        std::vector<std::string> m_dependingMaterials; // Bookkeeping for undo
    };
}