#pragma once

#include "le3_engine_systems.h"

namespace le3 {
    class LE3EditorComAddMaterial : public LE3EditorCommand { 
    public:
        LE3EditorComAddMaterial(std::string name, std::string shaderName);

        virtual void execute();
        virtual void undo();

    private:
        std::string m_name, m_shaderName;
    };
}