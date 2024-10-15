#pragma once

#include "le3_engine_systems.h"

namespace le3 {
    class LE3EditorComDeleteMaterial : public LE3EditorCommand { 
    public:
        LE3EditorComDeleteMaterial(std::string name, std::string shaderName);

        virtual void execute();
        virtual void undo();

    private:
        std::string m_name, m_shaderName;
        LE3Material m_material; // Note that this is not a pointer, since material is a struct anyway
        std::vector<std::pair<std::string, std::string>> m_depObjects;
    };
}